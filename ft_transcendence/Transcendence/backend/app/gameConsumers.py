
from channels.generic.websocket import AsyncWebsocketConsumer
from django.core.cache import cache
import asyncio
from asgiref.sync import sync_to_async
import uuid
import json
from app import utilsLogin
from app.models import Game, User
from asgiref.sync import sync_to_async  
from datetime import datetime
import redis
from django.contrib.auth.models import AnonymousUser
from django.utils import timezone
from channels.db import database_sync_to_async
import random

redis_conn = redis.Redis(host="redis", port=6379, db=0, decode_responses=True)

class GameConsumer(AsyncWebsocketConsumer): 
	async def connect(self):
		self.user = self.scope["user"]
		if isinstance(self.user, AnonymousUser):
			await self.close()
		else:
			try:
				await self.accept()
			except Exception as e:
				await self.sendError(e)
				await self.close()
				return
			self.finish = 0
			self.game_id = self.scope['url_route']['kwargs']['game_id']
			self.user = self.scope["user"] 
			self.keys_pressed = {"P1up":False, "P1down":False, "P2up":False,"P2down":False, "break":False}
			self.running = True

	async def receive(self, text_data):
		try:
			data = json.loads(text_data)
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
	
	async def set_first_co(self, data):
		game = await sync_to_async(Game.objects.get)(game_id=self.game_id)
		host = await database_sync_to_async(lambda: game.player1.username)()
		if (self.user.username == host):
			self.host = 1
		else :
			self.host = 0
		if self.channel_layer:
			await self.channel_layer.group_add(self.game_id, self.channel_name)
		if (self.host):
			self.game_settings = game.settings
			self.game_state_var = {
				"type":"game_state",
				"player1": {"pos" : 50, "score":0},
				"player2": {"pos":50, "score":0},
				"ball": {"x": 50, "y": 50, "dx": game.settings["ball_speed"], "dy": 0},
					"game_state": "waiting"
				}
			if (self.game_settings["number_of_player"] == 2):
				if (game.is_tournament_game != True):
					self.game_state_var["player1"]["username"] = self.user.username
				else:
					self.game_state_var["player1"]["username"] = self.game_settings["player1"]
				self.game_state_var["player2"]["username"] = self.game_settings["player2"]
			else:
				self.game_state_var["player1"]["username"] = self.user.username
				self.game_state_var["player2"]["username"] = "IA"
			await sync_to_async(game.save)()
			await self.start_countdown(3)

	async def start_countdown(self,i):
		if (i > 0):
			await self.channel_layer.group_send(
				self.game_id,
				{
					"type": "countdown",
					"message": str(i)
				}
			)
			await self.send(text_data=json.dumps(  {
					"type": "countdown",
					"message": str(i)
				}))
			await asyncio.sleep(1)
			await self.start_countdown(i - 1)
		else :
			await self.channel_layer.group_send(
				self.game_id,
				{
					"type": "start_game",
				}
			)

	async def game_state(self,data):
		if (self.host == 0):
			await self.send(text_data=json.dumps(data))

	async def start_game(self, data):
		await self.send(text_data=json.dumps({
			"type": "start_game"
		}))
		if (self.host):
			self.game_task = asyncio.create_task(self.gameLoop())

	async def countdown(self,data):
		await self.send(text_data=json.dumps({
				"type": "countdown",
				"message":data['message']
			}))

	async def input_p2(self, data):
		if (self.host):
			self.keys_pressed[data["input"]] = (data["key"] == "keydown")

	async def handle_input(self, data):
		input = data.get("input")
		player = data.get("sender")
		event_type = data.get("event")
		if (self.host and ((self.game_settings["local"]) == -1 or data.get("sender") == "p1")):
			p = 1
		else :
			p = 2
		if event_type == "keydown":
			if (input == "Up" and p == 1):
				self.keys_pressed["P1up"] = True
			if (input == "Down" and p == 1):
				self.keys_pressed["P1down"] = True
			if (input == "Up" and p == 2):
				await self.channel_layer.group_send(
				self.game_id,
				{
					"type": "input_p2",
					"input":"P2up",
					"key":'keydown'
				}
				)
			if (input == "Down" and p == 2):
				await self.channel_layer.group_send(
				self.game_id,
				{
					"type": "input_p2",
					"input":"P2down",
					"key":'keydown'
				}
				)
			if (input == "break" and p == 1):
				 self.keys_pressed["break"] = True
			if (input == "break" and p == 2):
				await self.channel_layer.group_send(
					self.game_id,
					{
						"type": "input_p2",
						"input":"break",
						"key":'keydown'
					}
					)
		elif event_type == "keyup":
			if (input == "Up" and p == 1):
				self.keys_pressed["P1up"] = False
			if (input == "Down" and p == 1):
				self.keys_pressed["P1down"] = False
			if (input == "Up" and p == 2):
				await self.channel_layer.group_send(
				self.game_id,
				{
					"type": "input_p2",
					"input":"P2up",
					"key":'keyup'
				}
				)
			if (input == "Down" and p == 2):
				await self.channel_layer.group_send(
				self.game_id,
				{
					"type": "input_p2",
					"input":"P2down",
					"key":'keyup'
				}
				)

	async def gameLoop(self):
		l = self.game_settings["paddle_size"]
		if (self.game_settings["view"] == 1):
			shift = 0
		else:
			shift = l/2
		touch = 1
		score_to_win = self.game_settings["score_to_win"]
		i = 0
		t = timezone.now()
		ia_input = str()
		game_state =self.game_state_var
		game_state["game_state"] = "on"
		kickoff = 1
		while self.running:
			if (game_state["game_state"] == "on"):
				if (self.keys_pressed["P1up"]):
					if (game_state["player1"]["pos"] > shift):
						game_state["player1"]["pos"] -= 1
				if (self.keys_pressed["P1down"]):
					if (game_state["player1"]["pos"] < 100 - l + shift):
						game_state["player1"]["pos"] += 1
				if (self.keys_pressed["P2up"]):
					if (game_state["player2"]["pos"] > shift):
						game_state["player2"]["pos"] -= 1
				if (self.keys_pressed["P2down"]):
					if (game_state["player2"]["pos"] < 100 - l + shift):
						game_state["player2"]["pos"] += 1
				if (self.keys_pressed["break"]):
					game_state["game_state"] = "break"
					self.keys_pressed["break"] = False
				if (self.host):
					kickoff = 1
					game_state["ball"]["x"] += game_state["ball"]["dx"]
					game_state["ball"]["y"] += game_state["ball"]["dy"]
					x = game_state["ball"]["x"]
					y = game_state["ball"]["y"]
					if (y + 0.3 > 100 and game_state["ball"]["dy"] > 0 or y < 0.3 and game_state["ball"]["dy"] < 0):
						 game_state["ball"]["dy"] = -game_state["ball"]["dy"]
					if (x < 0):
						game_state["ball"]["dx"] = -self.game_settings["ball_speed"]
						game_state["ball"]["dy"] = 0
						game_state["ball"]["x"] = 50
						game_state["ball"]["y"] = 50
						game_state["player1"]["pos"] = 50 - (self.game_settings["paddle_size"] / 2)
						game_state["player2"]["pos"] = 50 - (self.game_settings["paddle_size"] / 2)
						game_state["player2"]["score"] = game_state["player2"]["score"] + 1
						if (game_state["player2"]["score"] >= score_to_win):
							await self.channel_layer.group_send(
								self.game_id,
								{
									"type": "get_win",
									"score_player1":game_state["player1"]["score"],
									"score_player2":game_state["player2"]["score"],
									"winner":game_state["player2"]["username"],
									"loser":game_state["player1"]["username"],
									"result": f"{str(game_state['player2']['score'])} - {str(game_state['player1']['score'])}",
								}
								) 
					elif (x > 100):
						kickoff = 1
						touch = 1
						i = 119
						game_state["ball"]["dx"] = self.game_settings["ball_speed"]
						game_state["ball"]["dy"] = 0
						game_state["ball"]["x"] = 50
						game_state["ball"]["y"] = 50
						game_state["player1"]["pos"] = 50 - (self.game_settings["paddle_size"] / 2)
						game_state["player2"]["pos"] = 50 - (self.game_settings["paddle_size"] / 2)
						game_state["player1"]["score"] = game_state["player1"]["score"] + 1
						if (game_state["player1"]["score"] >= score_to_win):
							await self.channel_layer.group_send(
								self.game_id,
								{
									"type": "get_win",
									"score_player1":game_state["player1"]["score"],
									"score_player2":game_state["player2"]["score"],
									"winner":game_state["player1"]["username"],
									"loser":game_state["player2"]["username"],
									"result": f"{str(game_state['player1']['score'])} - {str(game_state['player2']['score'])}",
								}
								)
					elif(x < 2 and (y > game_state["player1"]["pos"] - 2 - shift and y <  game_state["player1"]["pos"] + (l + 2) - shift) and game_state["ball"]["dx"] < 0):
						kickoff = 0
						game_state["ball"]["dx"] = -(game_state["ball"]["dx"] - 0.03) 
						if (game_state["ball"]["dx"] > 0.9):
							game_state["ball"]["dx"] = 0.9
						game_state["ball"]["dy"] = (y - (game_state["player1"]["pos"] + (l/2) - shift ))/(l/2)
						touch = 1
					elif(x > 98 and (y > game_state["player2"]["pos"] - 2 - shift  and y <  game_state["player2"]["pos"] + (l + 2) - shift) and game_state["ball"]["dx"] > 0):
						kickoff = 0
						game_state["ball"]["dx"] = -(game_state["ball"]["dx"] + 0.03)
						if (game_state["ball"]["dx"] < -0.9):
							game_state["ball"]["dx"] = -0.9
						game_state["ball"]["dy"] = (y - (game_state["player2"]["pos"] + ((l) /2) - shift)) / (l/2) 
			elif (self.keys_pressed["break"] == True and game_state["game_state"] == "break"):
					game_state["game_state"] = "on"
					self.keys_pressed["break"] = False
			await self.send(text_data=json.dumps(game_state))
			await self.channel_layer.group_send(self.game_id,game_state)
			i = i + 1
			if (i > 120 and self.game_settings["number_of_player"] == 1 and touch == 1):
				i = 0
				touch = 0
				fdx = game_state["ball"]["dx"]
				fdy = game_state["ball"]["dy"]
				pos = game_state["player2"]["pos"]
				bx = x
				by = y
				d = (100 - x) / fdx
				while (bx < 98 and fdx > 0):
					bx= bx + fdx
					by = by + fdy
					if (by > 99.6 or by < 0.3):
						touch = touch + 1
						fdy = -fdy
				ia_input = await self.create_ia_input(touch, fdx, game_state["ball"]["dy"], by, d, pos,kickoff)
				touch = 0
			if (ia_input != ""):
				if (ia_input[0] == "u"):
					self.keys_pressed["P2up"] = True
					self.keys_pressed["P2down"] = False
				elif (ia_input[0] == "d"):
					self.keys_pressed["P2down"] = True
					self.keys_pressed["P2up"] = False
				else:
					self.keys_pressed["P2down"] = False
					self.keys_pressed["P2up"] = False
				if (len(ia_input) > 1):
					ia_input = ia_input[1:] 
				else:
					ia_input = ""
			await asyncio.sleep(1/120)

	async def create_ia_input(self,touch, fdx, dy, by, d, pos, kickoff):
		ia_input = ""
		i = 0
		if (self.game_settings["view"] != 1):
			pos = pos - self.game_settings["paddle_size"] / 2
		if (self.game_settings["paddle_size"] == 100/9):
			size_proba = 0.15
		elif (self.game_settings["paddle_size"] == 100/7):
			size_proba = 0.25
		elif (self.game_settings["paddle_size"] == 100/5):
			size_proba = 0.35
		else:
			size_proba = 0.25
		p = (0.4 - (abs(fdx) - 0.55)) + (0.2 - (abs(dy) / 5)) + size_proba
		if(kickoff):
			p = 1
		result = random.random()
		if (result < p):
			by = by - result * self.game_settings["paddle_size"] / p
			if (by < 0):
				by = 0
		else:
			if ((p + ((1 - p) / 2) < result and by < 100 - self.game_settings["paddle_size"]) or (by < self.game_settings["paddle_size"])):
				by = by + 3
			else :
				by = by - self.game_settings["paddle_size"] - 3
		while(i < d):
			if (abs(pos - by) / fdx > d - i - 10  or touch == 0):
				if (pos < by):
					ia_input = ia_input + "s"
					i = i + 1
					while(pos < by):
						ia_input = ia_input + "d"
						if (pos < 100 - self.game_settings["paddle_size"]):
							pos = pos + 1
						else :
							break
						i = i + 1
					break
				else:
					while(pos > by):
						ia_input = ia_input + "u"
						if (pos > 0):
							pos = pos - 1
						else:
							break
						i = i + 1
					break
			else :
				if (touch > 1 and i < d / 3):
					if (dy < 0):
						if (pos < 100 - self.game_settings["paddle_size"]):
							ia_input = ia_input + "d"
							pos = pos + 1
						else:
							ia_input = ia_input + "s"
					else:
						if (pos > 0):
							ia_input = ia_input + "u"
							pos = pos - 1
						else:
							ia_input = ia_input + "s"
				elif (touch == 2 and i > d / 3 and i < 2*d/3):
					if (dy > 0):
						if (pos < 100 - self.game_settings["paddle_size"]):
							ia_input = ia_input + "d"
							pos = pos + 1
						else:
							ia_input = ia_input + "s"
					else:
						if (pos > 0):
							ia_input = ia_input + "u"
							pos = pos - 1
						else:
							ia_input = ia_input + "s"
				elif (i > d/3):
					ran = random.random()
					if (ran < 0.33 and pos < 100 - self.game_settings["paddle_size"]):
						pos = pos + 1
						ia_input = ia_input + "d"
					elif(ran < 0.66 and pos > 0 and ran > 0.33):
						pos = pos - 1
						ia_input = ia_input + "u"
					else:
						ia_input = ia_input + "s"
			i = i + 1
		ia_input = ia_input + "s"
		return (ia_input)


	async def destroy_game(self, data):
		if (self.host):
			self.game_task.cancel()  # Arrête proprement la game loop


	@database_sync_to_async
	def set_win(self):
		self.user.total_wins = self.user.total_wins + 1
		self.user.total_matches = self.user.total_matches + 1
		if (self.host and  self.game_settings["number_of_player"] == 1):
			self.user.total_ai_matches = self.user.total_ai_matches + 1
		game = Game.objects.get(game_id=self.game_id)
		if (game.is_tournament_game):
			self.user.tournament_status = "Qualified"
			round = game.round_tournament
			round.winners.add(self.user)
			round.save()
			is_tournament_game = 1
		else:
			is_tournament_game = 0
		game.is_active = False
		game.winner = self.user
		self.user.save()
		game.save()
		return is_tournament_game

	
	@database_sync_to_async
	def set_lose(self):
		self.user.total_losses = self.user.total_losses + 1
		self.user.total_matches = self.user.total_matches + 1
		if (self.host and self.game_settings["number_of_player"] == 1):
			self.user.total_ai_matches = self.user.total_ai_matches + 1
		game = Game.objects.get(game_id=self.game_id)
		if (game.is_tournament_game):
			self.user.tournament_status = "Eliminated"
			round = game.round_tournament
			round.losers.add(self.user)
			round.save()
			is_tournament_game = 1
		else:
			is_tournament_game = 0
		game.is_active = False
		self.user.save()
		game.save()
		return is_tournament_game

	@database_sync_to_async
	def set_local_end(self):
		self.user.total_matches = self.user.total_matches + 1
		if (self.host and self.game_settings["number_of_player"] == 1):
			self.user.total_ai_matches = self.user.total_ai_matches + 1
		game = Game.objects.get(game_id=self.game_id)
		game.is_active = False
		self.user.save()
		game.save()

	@database_sync_to_async
	def set_disconnect(self, player_disconnect):
		if (self.host):
			self.game_task.cancel() 
		opps = User.objects.get(username=player_disconnect)
		self.user.total_matches = self.user.total_matches + 1
		game = Game.objects.get(game_id=self.game_id)
		game.is_active = False
		if (self.host):
			game.player1_score = 42
			game.player2_score = 0
		else:
			game.player1_score = 0
			game.player2_score = 42
		if (game.is_tournament_game):
			self.user.tournament_status = "Qualified"
			round = game.round_tournament
			round.winners.add(self.user)
			round.save()
			is_tournament_game = 1
		else:
			is_tournament_game = 0
		game.winner = self.user
		self.user.save()
		game.save()
		return is_tournament_game

	async def get_win(self,event):
		self.finish = 1
		is_tournament_game = 0
		if (event.get("result") == "disconnect"):
			is_tournament_game = await self.set_disconnect(event.get("player_disconnect"))
			if (is_tournament_game == 0):
				result ={
					"type":"disconnect",
					"user":self.user.username,
					"player_disconnect":event.get("player_disconnect"),
				}
			else :
				result ={
					"type":"result_tournament",
				}  
			await self.send(text_data=json.dumps(result))
			return
		if (self.host and self.game_settings["local"] == 1):
			type_game = "result"
			await self.set_local_end()
			game = await sync_to_async(Game.objects.get)(game_id=self.game_id)
			game.player1_score = event.get("score_player1")
			game.player2_score = event.get("score_player2")
			if (game.player1_score > game.player2_score):
				game.winner = self.user
			await sync_to_async(game.save)()
		else :
			game = await sync_to_async(Game.objects.get)(game_id=self.game_id)
			if (self.host):
				game.player1_score = event.get("score_player1")
				game.player2_score = event.get("score_player2")
				await sync_to_async(game.save)()
				self.running = 0
			if (self.user.username == event.get("winner") and game.is_tournament_game == False):
				is_tournament_game = await self.set_win()
			elif (self.user.username == event.get("loser") and game.is_tournament_game == False):
				is_tournament_game = await self.set_lose()
			elif (self.user.display_name == event.get("winner") and game.is_tournament_game == True):
				is_tournament_game = await self.set_win()
			elif (self.user.display_name == event.get("loser") and game.is_tournament_game == True):
				is_tournament_game = await self.set_lose()
			if (is_tournament_game == 1):
				type_game = "result_tournament"
			else:
				type_game = "result"
		result ={
			"type":type_game,
			"result": event.get("result"),	
			"winner": event.get("winner"),
			"loser": event.get("loser")
		}  
		await self.send(text_data=json.dumps(result))

	async def disconnect(self, close_code):
		try:
			await self.channel_layer.group_discard(self.game_id, self.channel_name)
			if (self.finish == 0):
				if (self.host and self.game_settings["local"] == 1):
					await self.set_local_end()
					game = await sync_to_async(Game.objects.get)(game_id=self.game_id)
					game.player1_score = 0
					game.player2_score = 0
					await sync_to_async(game.save)()
				else :
					await self.set_lose()
					await self.channel_layer.group_send(
						self.game_id,
						{
							"type": "get_win",
							"result":"disconnect",
							"player_disconnect":self.user.username,
						}
						) 
			if (self.host):
					self.game_task.cancel()  # Arrête proprement la game loop
		except Exception as e:
			print(f"Erreur lors de la suppression du groupe: {e}")

	async def sendError(self, error):
		await self.send(text_data=json.dumps({"error": str(error)}))
