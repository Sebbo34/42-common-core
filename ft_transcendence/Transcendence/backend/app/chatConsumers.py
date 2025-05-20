from channels.generic.websocket import AsyncWebsocketConsumer
import uuid
import json
from app import utilsLogin
from asgiref.sync import sync_to_async
from datetime import datetime
from django.contrib.auth.models import AnonymousUser
from app.models import Game, User
from app.models import Tournament, Round
from channels.db import database_sync_to_async
import asyncio

class ChatConsumer(AsyncWebsocketConsumer):
	async def connect(self):
		self.group_name = "live_chat"
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

	async def sendError(self, error):
		await self.send(text_data=json.dumps({"error": str(error)}))

	async def receive(self, text_data):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
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
	
	async def chat_message(self, msg):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		sender = msg.get("sender")
		blocked_list = msg.get("blocked_list")
		is_user_blocked = await self.user.is_user_blocked(sender)
		if self.user.username not in blocked_list and not is_user_blocked:
			await self.send(json.dumps(msg))

	async def send_message(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		chat_message = event.get("message")
		blocked_list = await self.user.get_blocked_list()
		msg = {
			"type": "chat_message",
			"message": chat_message,
			"sender": self.user.username,
			"blocked_list": blocked_list,
		}
		await self.channel_layer.group_send(self.group_name, msg)
	
	async def invite(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		blocked_list = await self.user.get_blocked_list()
		guest = event.get("target")
		invitation = {
			"type": "send_invit",
			"sender": self.user.username,
			"guest":guest,
			"blocked_list": blocked_list,
		}
		if (self.user.username != guest):
			await self.channel_layer.group_send(self.group_name, invitation)
	
	async def send_invit(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		sender = event.get("guest")
		blocked_list = event.get("blocked_list")
		is_user_blocked = await self.user.is_user_blocked(event.get("sender"))
		if (self.user.username == event.get("guest") and self.user.username not in blocked_list and not is_user_blocked):
			await self.send(json.dumps(event))
	
	async def accept_invit(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		host = event.get("host")
		acceptation = {
			"type": "send_acceptation",
			"sender": self.user.username,
			"host":host
		}
		if (self.user.username != host):
			await self.channel_layer.group_send(self.group_name, acceptation)
	
	async def send_acceptation(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		if (self.user.username == event.get("host")):
			await self.send(json.dumps(event))
		elif (self.user.username == event.get("sender")):
			waiting = {
				"type":"set_waiting",
				"host":event.get("host"),
			}
			await self.send(json.dumps(waiting))

	async def cancel_invitation(self, data):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		if (self.user.username == data.get("target")):
			await self.send(text_data=json.dumps({"type":"cancel_invitation",}))

	async def start_play(self, data):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		if (self.user.username == data.get("target")):
			await self.send(text_data=json.dumps({"type":"start_play",}))

	async def is_ready(self, data):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		invit = {
			"type": "start_play",
			"sender":self.user.username,
			"target": data.get("target"),
		}
		await self.channel_layer.group_send(self.group_name, invit)

	async def send_cancel(self, data):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		cancel = {
			"type": "cancel_invitation",
			"target": data.get("target"),
		}
		await self.channel_layer.group_send(self.group_name, cancel)
	async def reject_invit(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		host = event.get("host")
		rejection = {
			"type": "send_rejection",
			"sender": self.user.username,
			"host":host
		}
		if (self.user.username != host):
			await self.channel_layer.group_send(self.group_name, rejection)
	
	async def send_rejection(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		if (self.user.username == event.get("host")):
			await self.send(json.dumps(event))

	async def block(self, event):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		target = event.get("target")
		if (self.user.username != target ):
			await self.user.block_user(target)
			await self.send(text_data=json.dumps({
				"type": "block",
				"sender":event.get("target")
			}))	

	async def notice_tournament_game(self,msg):
		self.user  = await sync_to_async(User.objects.get)(id=self.user.id)
		if(self.user.id == msg.get("player1") or self.user.id == msg.get("player2")):
			notice = {
				"type": "Tournament_alert",
			}
			await self.send(text_data=json.dumps(notice))


class GsConsumer(AsyncWebsocketConsumer):
	async def connect(self):
		self.user = self.scope["user"]
		if isinstance(self.user, AnonymousUser):
			await self.close()
			return
		try:
			self.finish = 0 
			await self.accept()
			self.group_name = self.get_group_name(self.user.game_id)
			await self.channel_layer.group_add(self.group_name, self.channel_name)
			if not self.user.game_id:
				await self.send(text_data=json.dumps({"type":"disconnect","alert":"No game Found"}))
				return
			game = await sync_to_async(Game.objects.get)(game_id=self.user.game_id)
			if (game.is_active == False):
				await self.send(text_data=json.dumps({"type":"disconnect","alert":"No game Found"}))
			player1 = await self.get_player_username(game,1)
			if (player1 == self.user.username):
				player2 = await self.get_player_username(game,2)
				self.player1 = 1
				await self.send(text_data=json.dumps({"type":"display_settings","player2":player2}))
			else:
				self.player1 = 0
				await self.send(text_data=json.dumps({"type":"waiting",'gameSettings':""}))
		except Exception as e:
			await self.sendError(e)
			await self.close()
			return

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
	
	async def send_gs(self, data):
		gs = {
			"type":"waiting",
			"player2":data.get("player2"),
			"gameSettings":data.get("gameSettings"),
		}
		await self.channel_layer.group_send(self.group_name, gs)
	
	async def waiting(self,data):
		if(self.user.username == data.get("player2")):
			await self.send(text_data=json.dumps({"type":"waiting","gameSettings":data.get("gameSettings"),}))

	@sync_to_async
	def get_player_username(self, game, n):
		if (n == 1):
			return game.player1.username
		else :
			return game.player2.username

	async def start_play(self,data):
		self.finish = 1 
		if (self.player1 != 0):
			start = {
				"type":"start_play",
			}
			await self.channel_layer.group_send(self.group_name, start)
		if (self.player1 == 0):
			await self.send(text_data=json.dumps({"type":"start_play"}))

	def get_group_name(self,room_uuid):
		try:
			room_uuid = uuid.UUID(room_uuid, version=4)
			return f"chat_{str(room_uuid).replace('-', '')}"
		except ValueError:
			return "chat_invalid"

	async def send_deco(self, event):
		await self.send(text_data=json.dumps({"type":"disconnect"}))

	async def disconnect(self, close_code):
		try:
			await self.channel_layer.group_discard(self.group_name, self.channel_name)
			if (self.finish == 0):
				game = await sync_to_async(Game.objects.get)(game_id=self.user.game_id)
				game.is_active = False
				await sync_to_async(game.save)()
				await self.channel_layer.group_send(self.group_name,{"type":"send_deco",})
		except Exception as e:
			print(f"Erreur lors de la suppression du groupe: {e}")