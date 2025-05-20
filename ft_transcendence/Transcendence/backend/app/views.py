from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from app.models import User
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
from app import utilsLogin
from datetime import datetime
from django.utils import timezone
from datetime import timedelta
from rest_framework.permissions import IsAuthenticated
from rest_framework_simplejwt.authentication import JWTAuthentication
from django.shortcuts import redirect
from urllib.parse import urlencode
from django.conf import settings
import requests
from rest_framework.permissions import AllowAny
from rest_framework.views import APIView
from rest_framework.response import Response
from django.forms.models import model_to_dict
from .models import Game
from .serializers import *
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework import status
from .authentication import CookieJWTAuthentication
import uuid
from rest_framework_simplejwt.tokens import RefreshToken
from django.utils.crypto import get_random_string
from app.serializers import CustomRefreshToken
from django.db.models import Q
from rest_framework.exceptions import NotFound

class UserRegisterView(APIView):
	def post(self, request):
		serializer = UserSerializer(data=request.data)
		if serializer.is_valid():
			user = serializer.save()
			return Response({"message": f"User {user.username} has been successfully created"}, status=status.HTTP_201_CREATED)
		return Response (serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class UserLoginView(APIView):
	def post(self, request):
		serializer = UserLoginSerializer(data=request.data)
		if serializer.is_valid():
			user = serializer.validated_data["user"]
			temp_token = utilsLogin.generateTempJWT(user)
			utilsLogin.send2FAEmail(user)
			response = Response(
				{"message": "A code has been sent to you by e-mail"}, 
				status=status.HTTP_200_OK
			)
			response.set_cookie(
				key="temp_token",
				value=temp_token,
				max_age=24*3600,
				httponly=True,
				secure=settings.SESSION_COOKIE_SECURE,
				samesite="Lax"
			)
			return response
		return Response(serializer.errors, status=status.HTTP_401_UNAUTHORIZED)

class UserLogoutView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def post(self, request):
		request.user.is_online = False
		request.user.save()
		response = Response({"message": "User logged out successfully."}, status=status.HTTP_200_OK)
		response.delete_cookie("access_token", path='/')
		return response

class Verify2FAView(APIView):
	def post(self, request):
		temp_token = request.COOKIES.get("temp_token")
		if not temp_token:
			return Response(
				{"message": "Error. Token not found."},
				status=status.HTTP_400_BAD_REQUEST
			)
		code2fa = request.data.get("code")
		if not code2fa:
			return Response(
				{"message": "Error. Code is missing."},
				status=status.HTTP_400_BAD_REQUEST
			)
		decoded_token = utilsLogin.decodeJWT(temp_token)
		if not decoded_token:
			return Response(
				{"message": "Error. Invalid or expired token."},
				status=status.HTTP_400_BAD_REQUEST
			)
		try:
			user = User.objects.get(username=decoded_token["username"])
		except Exception:
			return Response(
				{"message": "Error. User not found."},
				status=status.HTTP_400_BAD_REQUEST
			)	
		try:
			if code2fa != user.two_factor_code.code or timezone.now() > user.two_factor_code.expiry:
				return Response(
					{"message": "Error. Code expired."},
					status=status.HTTP_400_BAD_REQUEST
				)
		except Exception:
			return Response(
				{"message": f"Error. No code found for this user."},
				status=status.HTTP_400_BAD_REQUEST
			)			
		
		access_token = utilsLogin.generateJWT(user)
		response = Response(
			{"message": "Successful login!"}, 
			status=status.HTTP_200_OK
		)
		response.set_cookie(
			key="access_token",
			value=access_token,
			max_age=24*3600,
			httponly=True,
			secure=settings.SESSION_COOKIE_SECURE,
			samesite="Lax"
		)
		return response		

class UserLogin42View(APIView):
	def get(self, request):
		query_params = urlencode({
			"client_id": settings.OAUTH_CLIENT_ID,
			"redirect_uri": settings.OAUTH_REDIRECT_URI,
			"response_type": "code",
			"scope": "public"
		})
		return redirect(f"{settings.OAUTH_AUTH_URL}?{query_params}")

class CallbackView(APIView): 
	def get(self, request):
		auth_code = request.GET.get("code")
		if not auth_code:
			return Response({"error": "Authorization code is missing"}, status=status.HTTP_400_BAD_REQUEST)
		response_token = requests.post(
			url=settings.OAUTH_TOKEN_URL,
			data={
				"client_id": settings.OAUTH_CLIENT_ID,
				"client_secret": settings.OAUTH_CLIENT_SECRET,
				"code": auth_code,
				"redirect_uri": settings.OAUTH_REDIRECT_URI,
				"grant_type": "authorization_code"
			}
		)
		if not response_token.status_code == status.HTTP_200_OK:
			return Response({"error": "Token retrieval failure"}, status=status.HTTP_400_BAD_REQUEST)
		
		data_response_token = response_token.json()
		access_token = data_response_token["access_token"]

		response_data_user = requests.get(
			url=settings.OAUTH_USER_INFO_URL,
			headers={"Authorization": f"Bearer {access_token}"}
		)
		if not response_data_user.status_code == status.HTTP_200_OK:
			return Response({"error": "Failure to retrieve user info"}, status=status.HTTP_400_BAD_REQUEST)
		
		data_response_info = response_data_user.json()
		try:
			user = User.objects.get(login42=data_response_info["login"])
		except Exception:
			user = User.objects.create(
				login42=data_response_info["login"],
				username=data_response_info["login"]				
			)

		user.is_online = True
		user.save()
		access_token = utilsLogin.generateJWT(user)
		response = redirect(settings.REDIRECT_HOME_PAGE)
		response.set_cookie(
			key="access_token",
			value=access_token,
			max_age=24*3600,
			httponly=True,
			secure=settings.SESSION_COOKIE_SECURE,
			samesite="Lax"
		)
		
		return response

class UserProfileView(APIView):
	permission_classes = [IsAuthenticated]
	authentication_classes = [CookieJWTAuthentication]

	def get(self, request):
		friend_name = request.data.get("friend_name")
		if not friend_name:
			user = request.user
		else:
			try:
				user = User.objects.get(username=friend_name)
			except Exception:
				return Response(
					{"message": "Error. User not found."},
					status_code=status.HTTP_404_NOT_FOUND
				)
		serializer = UserSerializer(user)
		return Response(serializer.data, status=status.HTTP_200_OK)

	def post(self, request):
		friend_name = request.data.get("friend_name")
		if not friend_name:
			user = request.user
		else:
			try:
				user = User.objects.get(username=friend_name)
			except Exception:
				return Response(
					{"message": "Error. User not found."},
					status_code=status.HTTP_404_NOT_FOUND
				)
		serializer = UserSerializer(user)
		return Response(serializer.data, status=status.HTTP_200_OK)

class UpdateProfileView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def put(self, request):
		user = request.user
		old_username = user.username

		if user.login42 != "temp_login":
			serializer = User42Serializer(user, data=request.data, partial=True)
		else:
			serializer = UserSerializer(user, data=request.data, partial=True)

		if serializer.is_valid():
			updated_user = serializer.save()

			if user.login42 == "temp_login" and "username" in request.data and old_username != updated_user.username:
				users_to_update = User.objects.filter(blocked_list__contains=[old_username])
				for u in users_to_update:
					u.blocked_list = [
						updated_user.username if name == old_username else name
						for name in u.blocked_list
					]
					u.save()

			refresh = CustomRefreshToken.for_user(updated_user)
			access_token = str(refresh.access_token)
			refresh_token = str(refresh)

			response_data = {
				"message": f"User {updated_user.username}'s infos have been successfully updated!",
				"username": updated_user.username,
				"avatar": updated_user.avatar.url if updated_user.avatar else None,
			}
			if user.login42 == "temp_login":
				response_data["email"] = updated_user.email

			response = Response(response_data, status=status.HTTP_200_OK)
			response.set_cookie(
				key="access_token",
				value=access_token,
				max_age=24*3600,
				httponly=True,
				secure=settings.SESSION_COOKIE_SECURE,
				samesite="Lax"
			)
			response.set_cookie(
				key="refresh_token",
				value=refresh_token,
				max_age=24*3600,
				httponly=True,
				secure=settings.SESSION_COOKIE_SECURE,
				samesite="Lax"
			)
			return response

		return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class AddFriendView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def post(self, request):
		user = request.user
		friend_username = request.data.get("friend_to_add")
		try:
			friend = User.objects.get(username=friend_username)
		except User.DoesNotExist:
			return Response({"message": "User not found"}, status=status.HTTP_404_NOT_FOUND)
		if user.friends.filter(id=friend.id).exists():
			return Response({"message": "User already your friend"}, status=status.HTTP_400_BAD_REQUEST)
		if user == friend:
			return Response({"message": "User is yourself, a bit narcissistic are we?"}, status=status.HTTP_400_BAD_REQUEST)
		user.friends.add(friend)
		return Response({"message": "Friend successfully added!"}, status=status.HTTP_200_OK)


class RemoveFriend(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def post(self, request):
		user = request.user
		friend_username = request.data.get("friend_to_remove")
		try:
			friend = User.objects.get(username=friend_username)
		except User.DoesNotExist:
			return Response({"message": "User not found"}, status=status.HTTP_404_NOT_FOUND)
		if not user.friends.filter(id=friend.id).exists():
			return Response({"message": "User is not your friend"}, status=status.HTTP_400_BAD_REQUEST)
		if user == friend:
			return Response({"message": "User is yourself, a bit narcissistic are we?"}, status=status.HTTP_400_BAD_REQUEST)
		user.friends.remove(friend)
		return Response({"message": "Friend successfully removed!"}, status=status.HTTP_200_OK)


class FriendsListView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def get(self, request):
		user = request.user
		
		friends_user = list(user.friends.values("username", "avatar", "is_online"))

		for friend in friends_user:
			if friend["avatar"]:
				friend["avatar"] = settings.MEDIA_URL + friend["avatar"]
			else:
				friend["avatar"] = settings.MEDIA_URL + "avatars/default.png"

		if not friends_user:
			return Response({"message": "You have no friends yet"}, status=status.HTTP_200_OK)

		return Response(
			{
				"message": "Here is your friends list!",
				"friends": friends_user,
			},
			status=status.HTTP_200_OK
		)


class GameInfoView(APIView):
    authentication_classes = [CookieJWTAuthentication]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        user = request.user
        if not user.game_id:
            return Response({"message": "No game_id associated with user."}, status=status.HTTP_400_BAD_REQUEST)

        try:
            game = Game.objects.get(game_id=user.game_id)
        except Game.DoesNotExist:
            raise NotFound(detail="Game not found.")

        if game.is_active:
            return Response({"game": model_to_dict(game)}, status=status.HTTP_200_OK)
        else:
            return Response({"message": "Game is not active."}, status=status.HTTP_400_BAD_REQUEST)


class MatchHistoryView(APIView):
	authentication_classes = [CookieJWTAuthentication]

	def get(self, request):
		friend_name = request.query_params.get("friend_name")
		if not friend_name:
			user = request.user
		else:
			try:
				user = User.objects.get(username=friend_name)
			except Exception:
				return Response(
					{"message": "Error. User not found."},
					status_code=status.HTTP_404_NOT_FOUND
				)
		all_games = user.gamesPlayed().filter(~Q(player1_score=0, player2_score=0)).order_by("-date")
		serializer = GameHistorySerializer(all_games, many=True)
		return Response(serializer.data, status=status.HTTP_200_OK)

	def post(self, request):
		friend_name = request.data.get("friend_name")
		if not friend_name:
			user = request.user
		else:
			try:
				user = User.objects.get(username=friend_name)
			except Exception:
				return Response(
					{"message": "Error. User not found."},
					status_code=status.HTTP_404_NOT_FOUND
				)
		all_games = user.gamesPlayed().filter(~Q(player1_score=0, player2_score=0)).order_by("-date")
		serializer = GameHistorySerializer(all_games, many=True)
		return Response(serializer.data, status=status.HTTP_200_OK)

class GameLocalView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def post(self, request):
		user = request.user
		game_id = str(uuid.uuid4())
		game = Game.objects.create(
			game_id=game_id,
			game_name=f"game_{game_id}",
			nb_players=1,
			is_available=False,
			player1=user,
			date =datetime.now(),
			player2 = user,
			settings = request.data,
			is_active= True
		)
		game.save()
		user.game_id = game_id
		user.save()
		return Response({"message": f"{request.data}Game successfully be created"}, status=status.HTTP_200_OK)


class GameWithoutLobbyView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]
	def post(self, request):
		user = request.user
		game_id = str(uuid.uuid4())
		target = User.objects.get(username=request.data["target"])
		target.game_id = game_id
		target.save()
		gameSettings = { 
			"paddle_size": 100/7,
			"ball_speed": 0.7,
			"view": 1,
			"score_to_win": 7,
			"player1": "player1",
			"player2": "player2",
			"number_of_player":2,
			"local": -1
		}
		game = Game.objects.create(
			game_id=game_id,
			game_name=f"Game of {game_id}",
			nb_players=1,
			is_available=False,
			player1=user,
			date = datetime.now(),
			player2 = target,
			settings = gameSettings,
			is_active= True
		)
		game.save()
		user.game_id = game_id
		user.save()
		return Response({"message": "Game successfully be created"}, status=status.HTTP_200_OK)

class GameSettingsWithoutLobbyView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def post(self, request):
		user = request.user
		game = Game.objects.get(game_id=user.game_id)
		request.data["player1"] = user.username
		request.data["player2"] = game.player2.username
		game.settings = request.data
		game.save()
		return Response({"message": f"Settings sucessfully sets"}, status=status.HTTP_200_OK)


class LocalGameSettingsView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def post(self, request):
		user = request.user
		nb_players = request.data.get("nb_players")
		if not nb_players:
			return Response(
				{"error": "Number of players is required."},
				status=status.HTTP_400_BAD_REQUEST
			)
		
		guest_user = User.objects.create(
			username=f"guest_{get_random_string(14)}",
			is_active=False
		)
		guest_user.set_password(get_random_string(15))
		guest_user.save()

		game_id = str(uuid.uuid4())
		game = Game.objects.create(
			game_id=game_id,
			game_name=f"game_{game_id}",
			nb_players=nb_players,
			is_available=False,
			player1=user,
			date=timezone.now(),
			player2=guest_user,
			is_active=True
		)
		game.save()
		user.game_id = game_id
		user.save()
		return Response(
			{"message": f"{game.game_name} successfully created!"},
			status=status.HTTP_201_CREATED
		)

class MyInfosView(APIView):
	authentication_classes = [CookieJWTAuthentication]

	def get(self, request):
		response = Response(
			{
				"username": None,
				"is_online": False
			},
			status=status.HTTP_401_UNAUTHORIZED
		)

		try :
			user = request.user
			if not user.is_authenticated:
				return response
			username = user.username
		except Exception:
			return response	
			
		return Response(
			{
				"username": username,
				"is_online": user.is_online
			},
			status=status.HTTP_200_OK
		)

class AllUsersView(APIView):
	authentication_classes = [CookieJWTAuthentication]
	permission_classes = [IsAuthenticated]

	def get(self, request):
		users = User.objects.all().values("username", "avatar")
		if users:
			return Response(
				users,
				status=status.HTTP_200_OK
			)