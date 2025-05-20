from channels.generic.websocket import AsyncWebsocketConsumer
import uuid
import json
import base64
from django.core.files.base import ContentFile
from app import utilsLogin
from asgiref.sync import sync_to_async
from datetime import datetime
from django.contrib.auth.models import AnonymousUser
from app.models import Game, User
from app.models import Tournament, Round
from channels.db import database_sync_to_async
from app.utilsLogin import (
	getAvailableTournamentDecorator,
	getUserDecorator,
	createRoundDecorator,
	createTournamentDecorator,
	createGameDecorator,
	addPlayerToRoundDecorator,
	addPlayerToTournamentDecorator,
	addRoundToTournamentDecorator,
	getTournamentDecorator,
	getLosersInRoundDecorator,
	getRoundGamesDecorator,
	getTournamentPlayersDecorator,
	getRoundPlayersDecorator,
	getActiveTournamentDecorator,
	getCurrentRound,
	removePlayerFromRound,
	removePlayerToTournamentDecorator,
	getTournamentRoundsDecorator,
	getWinnersInRoundDecorator,
	isOppenentReadyDecorator,
	changeTournamentStatus,
	getOpponent,
	changeGameId,
	getOldRound,
	linkRoundToTournamentDecorator,
	changeDisplayName,
	checkDisplayName,
	changeTournamentSettings
)



class TournamentLobbyConsumer(AsyncWebsocketConsumer):
	async def connect(self):
		self.group_name = "lobby_tournament"
		self.user = self.scope["user"]
		if isinstance(self.user, AnonymousUser):
			await self.close()
		else:
			try:
				await self.accept()
				await self.channel_layer.group_add(self.group_name, self.channel_name)
			except Exception as e:
				await self.sendError(e)
				await self.close()
				return
			tournament = await getAvailableTournamentDecorator()
			if not tournament == None:
				self.tournament_id = tournament.tournament_id
				await self.send_available_tournament({"available_tournament":tournament.tournament_name})
			else :
				tournament = await getActiveTournamentDecorator()
				if not tournament == None:
					self.tournament_id = tournament.tournament_id
					duel = []
					await self.channel_layer.group_add(tournament.tournament_name, self.channel_name)
					current_round = await getCurrentRound(tournament)
					winners = await getWinnersInRoundDecorator(current_round)
					if(len(winners) == 2 and current_round.round_number == 2 and self.user in winners):
						finale = await createRoundDecorator(1)
						await linkRoundToTournamentDecorator(finale, tournament)
						for winner in winners:
							await addPlayerToRoundDecorator(finale, winner)
							duel.append(winner)
							await changeTournamentStatus(winner, "", "Unready")
							
						game_id = str(uuid.uuid4())
						await addRoundToTournamentDecorator(tournament, finale)
						await self.channel_layer.group_send(
							"live_chat",
							{
								"type": "notice_tournament_game",
								"message": "The game starts!",
								"player1":duel[0].id,
								"player2":duel[1].id,
							}
						)
						await changeTournamentSettings(tournament, duel[0].display_name, duel[1].display_name)
						game = await createGameDecorator(game_id, duel[0], duel[1], tournament, tournament.settings, finale)
						await database_sync_to_async(tournament.save)()
					if(len(winners) == 1 and current_round.round_number == 1):
						await self.channel_layer.group_send(tournament.tournament_name,{"type": "send_active_tournament","winner":1})
					else:
						await self.channel_layer.group_send(tournament.tournament_name,{"type": "send_active_tournament",})
				else:
					await self.send(text_data=json.dumps({
						"type": "display_create",
					}))
	async def sendError(self, error):
		await self.send(text_data=json.dumps({"error": str(error)}))

	async def receive(self, text_data):
		try:
			data = json.loads(text_data)
			await self.send(json.dumps(text_data))
		except json.JSONDecodeError:
			return
		if "type" not in data:
			return
		event_type = data["type"]
		handler = getattr(self, event_type, None)
		if handler:
			await handler(data)
		else:
			print(f"⚠️ Pas de méthode trouvée pour le type '{event_type}'")

	async def disconnect(self,errror):
		await self.channel_layer.group_discard(self.group_name, self.channel_name)
		
	async def create_tournament(self, data):
		available_tournament = await getAvailableTournamentDecorator()
		active_tournament = await getActiveTournamentDecorator()
		if not available_tournament is None:
			await self.sendError("Unable to create a tournament. Please join the available tournament.")
		elif not active_tournament is None:
			await self.sendError("Unable to create a tournament. Please wait until the end of the current tournament.")
		else:
			if (data.get("display_name") != ""):
				await changeDisplayName(self.user, data.get("display_name"))
			else :
				await changeDisplayName(self.user, self.user.username)
			self.channel_layer.group_discard(self.group_name, self.channel_name)
			first_round = await createRoundDecorator(2)
			await addPlayerToRoundDecorator(first_round, self.user)
			tournament_id = str(uuid.uuid4())
			tournament = await createTournamentDecorator(tournament_id, first_round, data.get("gameSettings"))
			await linkRoundToTournamentDecorator(first_round, tournament)
			await addPlayerToTournamentDecorator(tournament, self.user)
			await addRoundToTournamentDecorator(tournament, first_round)
			await database_sync_to_async(tournament.save)()
			self.tournament_id = tournament.tournament_id
			await self.channel_layer.group_add(tournament.tournament_name, self.channel_name)
			msg = {
				"type": "tournament_registration",
				"message": f"You are registered for {tournament.tournament_name}",
				"available_tournament": tournament.tournament_name,
			}
			await changeTournamentStatus(self.user, "", "Register")
			await self.channel_layer.group_send(tournament.tournament_name,msg)
	
	async def join_tournament(self, data):
		tournament_id = data.get("tournament_id")
		try:
			tournament = await getTournamentDecorator(tournament_id)
		except Exception as e:
			await self.sendError(e)
			return
		if (data.get("display_name") != ""):
			check = await checkDisplayName(tournament, data.get("display_name"))
			if (check):
				await changeDisplayName(self.user, data.get("display_name"))
			else:
				await self.send_available_tournament({})
				return
		else:
			check = await checkDisplayName(tournament, self.user.username)
			if (check):
				await changeDisplayName(self.user, self.user.username)
			else:
				await self.send_available_tournament({})
				return
		players = await getTournamentPlayersDecorator(tournament)
		if self.user in players:
			return
		self.channel_layer.group_discard(self.group_name, self.channel_name)
		tournament.nb_players += 1
		current_round = await getCurrentRound(tournament)
		await addPlayerToTournamentDecorator(tournament, self.user)
		await addPlayerToRoundDecorator(current_round, self.user)
		await database_sync_to_async(tournament.save)()
		await self.channel_layer.group_add(tournament.tournament_name, self.channel_name)
		if tournament.isFull():
			await changeTournamentStatus(self.user, "", "Register")
			tournament.is_available = False
			tournament.is_active = True
			await database_sync_to_async(tournament.save)()
			await self.create_duels(tournament)
		else :
			msg = {
				"type": "tournament_registration",
				"message": f"You are registered for {tournament.tournament_name}",
				"available_tournament":tournament.tournament_name,
			}
			await changeTournamentStatus(self.user, "", "Register")
			await self.channel_layer.group_send(tournament.tournament_name,msg)
	
	async def tournament_registration(self,data):
		await self.send(text_data=json.dumps({
				"type": "tournament_registration",
				"message":data.get("message"),
				"available_tournament":data.get("available_tournament"),
			}))

	async def change_status(self,data):
		await changeTournamentStatus(self.user, "", data.get("status"))
		status = {
			"type": "start_tournament",
			"available_tournament":data.get("tournament_id"),
		}
		tournament_name = "tournament_" + self.tournament_id
		await self.channel_layer.group_send(tournament_name, status)


	async def unjoin_tournament(self,data):
		try:
			tournament = await getTournamentDecorator(self.tournament_id)
		except Exception as e:
			await self.sendError(e)
			return
		players = await getTournamentPlayersDecorator(tournament)
		if self.user in players:
			tournament.nb_players -= 1
			await changeTournamentStatus(self.user, "", "Unregistered")
			current_round = await getCurrentRound(tournament)
			await removePlayerToTournamentDecorator(tournament, self.user)
			await removePlayerFromRound(current_round, self.user)
			await database_sync_to_async(tournament.save)()
			await database_sync_to_async(current_round.save)()
			if (tournament.nb_players == 0):
				tournament.is_available = False
				await database_sync_to_async(tournament.save)()
			msg = {
				"type": "tournament_registration",
				"message": f"You are unregistered for {tournament.tournament_name}",
				"available_tournament":tournament.tournament_name,
			}
			await self.channel_layer.group_send(tournament.tournament_name,msg)

	@database_sync_to_async
	def update_user(self, user,game_id):
		user.game_id = game_id
	async def create_duels(self, tournament):
		try:
			tournament = await getTournamentDecorator(self.tournament_id)
		except Exception as e:
			await self.sendError(e)
			return
		i = 0
		duel = []
		name = []
		rnd = await getCurrentRound(tournament)
		gameSettings = {
			"paddle_size": 100/7,
			"ball_speed": 0.7,
			"view": 1,
			"score_to_win": 7,
			"player1": "a",
			"player2": "a",
			"number_of_player":2,
			"local": -1
		}
		tournament_players = await getRoundPlayersDecorator(rnd)
		for player in tournament_players:
			if i < 2:
				duel.append(player)
				name.append(player.id)
				i += 1
				if (i > 1):
					game_id = str(uuid.uuid4())
					await changeTournamentSettings(tournament, duel[0].display_name, duel[1].display_name)
					game = await createGameDecorator(game_id, duel[0], duel[1], tournament, tournament.settings, rnd)
					duel = []
					i = 0
		await self.channel_layer.group_send(
			tournament.tournament_name,
			{
				"type": "start_tournament",
				"active_tournament":tournament.tournament_name,
			}
		)
		await self.channel_layer.group_send(
			"live_chat",
			{
				"type": "notice_tournament_game",
				"message": "The game starts!",
				"player1":name[0],
				"player2":name[1],
			}
		)
		await self.channel_layer.group_send(
			"live_chat",
			{
				"type": "notice_tournament_game",
				"message": "The game starts!",
				"player1":name[2],
				"player2":name[3],
			}
		)

	async def start_tournament(self, tournament):
		await self.send(text_data=json.dumps({
			"type": "start_tournament",
			"active_tournament":tournament.get("active_tournament"),
		}))

	async def start_tournament_game(self, tournament):
		if (tournament.get("player1") == self.user.id or tournament.get("player2") == self.user.id):
			await self.send(text_data=json.dumps({
				"type": "start_tournament_game",
			}))

	async def send_available_tournament(self, event):
		try:
			tournament = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
			current_round = await getCurrentRound(tournament)
			players = await getRoundPlayersDecorator(current_round)
			player_data = [
				{
					"username": player.display_name,
					"tournament_status":player.tournament_status,
					"profile_picture": (
						f"data:image/png;base64,{base64.b64encode(player.avatar.read()).decode('utf-8')}"
						if player.avatar else None
					)
				}
			for player in players
			]
			if self.user in players:
				user_in = self.user.display_name
			else:
				user_in = ""
			await self.send(text_data=json.dumps({
				"type": "available_tournament",
				"players":{2:player_data,1:[],"tournament":tournament.tournament_id,},
				"user_in":user_in,
			}))
		except Tournament.DoesNotExist:
			await self.send(text_data=json.dumps({
				"error": "Tournament not found"
			}))

	async def send_active_tournament(self, event):
		try:
			if (self.user.tournament_status == "Register"):
				await changeTournamentStatus(self.user, "", "Unready")
			tournament = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
			current_round = await getCurrentRound(tournament)
			self.opponent = await getOpponent(self.user, current_round)
			player_json = {
				"tournament":tournament.tournament_id,
				2:[],
				1:[],
				}
			players = await getRoundPlayersDecorator(current_round)
			winners = await getWinnersInRoundDecorator(current_round)
			losers = await getLosersInRoundDecorator(current_round)
			if (current_round.round_number == 1):
				round = await getOldRound(tournament)
				old_winners = await getWinnersInRoundDecorator(round)
				players = await getRoundPlayersDecorator(round)
				player_json[round.round_number] = [
					{
						"username": player.display_name,
						"tournament_status": (
							"Qualified" if player in old_winners else "Eliminated"
						),
						"profile_picture": (
							f"data:image/png;base64,{base64.b64encode(player.avatar.read()).decode('utf-8')}"
							if player.avatar else None
						)
					}
					for player in players
				]
			players = await getRoundPlayersDecorator(current_round)
			player_json[current_round.round_number] = [
				{
					"username": player.display_name,
					"tournament_status":player.tournament_status,
					"profile_picture": (
						f"data:image/png;base64,{base64.b64encode(player.avatar.read()).decode('utf-8')}"
						if player.avatar else None
					)
				}
			for player in players
			]
			if self.user in players and  self.user not in winners and  self.user not in losers:
				user_in = self.user.display_name
			else:
				user_in = ""
			if event.get("winner") is not None:
				winner = winners[0]
				player_json["winner"] = {
					"username": winner.display_name,
						"tournament_status": "Winner",
						"profile_picture": (
							f"data:image/png;base64,{base64.b64encode(winner.avatar.read()).decode('utf-8')}"
							if winner.avatar else None
						)
				}
			await self.send(text_data=json.dumps({
				"type": "active_tournament",
				"players":player_json,
				"user_in":user_in,
			}))
		except Tournament.DoesNotExist:
			await self.send(text_data=json.dumps({
				"error": "Tournament not found"
			}))

	async def sendError(self, e):
		await self.send(json.dumps({
			"type": "error",
			"message": f"An error has occured: {str(e)}"
		}))
	async def get_ready(self,data):
		if hasattr(self, 'opponent'):
			tournament = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
			is_oppenent_ready = await isOppenentReadyDecorator(self.opponent)
			if (is_oppenent_ready == True):
				current_round = await getCurrentRound(tournament)
				await changeGameId(current_round, self.user, self.opponent)
				await self.send(text_data=json.dumps({
					"type": self.user.tournament_status,
					"set":self.user.game_id,
				}))
				await changeTournamentStatus(self.user, self.opponent, "InGame")
				status = {
					"type":"start_tournament_game",
					"player1":self.user.id,
					"player2":self.opponent,
				}
				await self.channel_layer.group_send(tournament.tournament_name, status)
			else:
				await changeTournamentStatus(self.user, "", "Ready")
				status = {
					"type": "start_tournament",
					"available_tournament":data.get("tournament_id"),
				}
				tournament_name = "tournament_" + self.tournament_id
				await self.channel_layer.group_send(tournament_name, status)

	async def set_unactive(self,data):
		tournament = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
		tournament.is_active = False
		await database_sync_to_async(tournament.save)()

