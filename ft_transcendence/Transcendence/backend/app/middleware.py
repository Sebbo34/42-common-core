from urllib.parse import parse_qs
from django.contrib.auth.models import AnonymousUser
from channels.db import database_sync_to_async
from channels.middleware import BaseMiddleware
from channels.auth import AuthMiddlewareStack
from django.contrib.auth import get_user_model
from app import utilsLogin
from django.contrib.auth.models import User
from app.models import User
from asgiref.sync import sync_to_async
from rest_framework_simplejwt.tokens import AccessToken
from django.conf import settings
from django.http import HttpResponseRedirect

async def get_user_from_token(token):
	try:
		# Décoder le token et récupérer le username
		decoded_data = utilsLogin.decodeJWT(token)
		username = decoded_data["username"]
		if username:
			user = await sync_to_async(User.objects.get)(username=username)
			return user
		else:
			return None
	except Exception as e:
		print(f"Error decoding token: {e}")
		return None



class WebSocketAuthMiddleware(BaseMiddleware):
	""" Middleware WebSocket qui récupère le token JWT depuis les cookies `HttpOnly`. """

	async def __call__(self, scope, receive, send):
		headers = dict(scope["headers"])  # Récupère les headers WebSocket
		# Vérifie si le cookie JWT est présent dans les headers
		cookie_header = headers.get(b'cookie', b'').decode()
		token = None
		for cookie in cookie_header.split("; "):
			if cookie.startswith("access_token="):  # Si ton token est stocké sous "access_token"
				token = cookie.split("=")[1]
		
		# Vérifier et authentifier l'utilisateur avec le token JWT
		if token:
			try:
				decoded_token = AccessToken(token)  # Décode le JWT
				scope["user"] = await get_user_from_token(token)
			except Exception as e:
				print(f"Erreur d'authentification JWT : {e}")
				scope["user"] = AnonymousUser()
		else:
			scope["user"] = AnonymousUser()

		return await super().__call__(scope, receive, send)


# Stack Middleware pour inclure notre middleware dans le routing WebSocket
def WebSocketMiddlewareStack(inner):
	return WebSocketAuthMiddleware(AuthMiddlewareStack(inner))

