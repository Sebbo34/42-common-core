from django.core.mail import send_mail
from app import models
import jwt
from django.utils import timezone
from datetime import timedelta
from django.conf import settings
import uuid
from rest_framework.authentication import TokenAuthentication
from rest_framework.exceptions import AuthenticationFailed
from app.models import Tournament, User, Round, Game
from channels.db import database_sync_to_async

def send2FAEmail(user):
	models.TwoFactorCode.objects.filter(user=user).delete()
	twoFA = models.TwoFactorCode.objects.create(user=user)
	twoFA.generateCode()
	subject = "Your authentication code"
	message = f"Hi {user.username},\nYour code is: {twoFA.code}.\nIt expires in 10 minutes!"
	sender = settings.DEFAULT_FROM_EMAIL
	recipient_list = [user.email]
	send_mail(subject, message, sender, recipient_list)

def generateJWT(user):
	expiry = timezone.now() + timedelta(seconds=24*3600)  # UTC pour éviter les erreurs de fuseau horaire
	payload = {
		"jti": str(uuid.uuid4()),  # Générer un identifiant unique pour le token
		"username": user.username,
		"iat": int(timezone.now().timestamp()),
		"exp": int(expiry.timestamp()),
		"token_type": "access",
		"creation": timezone.now().isoformat()
	}
	token = jwt.encode(payload, settings.SECRET_KEY_JWT, algorithm="HS256")
	return token

def generateTempJWT(user):
	expiry = timezone.now() + timedelta(minutes=10)
	payload = {
		"username": user.username,
		"exp": int(expiry.timestamp()),
		"token_type": "temp",
		"iat": int(timezone.now().timestamp())
	}
	token = jwt.encode(payload, settings.SECRET_KEY_JWT, algorithm="HS256")
	return token

def decodeJWT(token):
	try:
		payload = jwt.decode(jwt=token, key=settings.SECRET_KEY_JWT, algorithms=["HS256"])
		return payload
	except jwt.ExpiredSignatureError:
		return None
	except jwt.InvalidKeyError:
		return None
	except jwt.InvalidTokenError:
		return None

def get_token_from_request(request):
	auth = request.headers.get("Authorization", None)
	if auth is None:
		raise AuthenticationFailed("No token provided")
	if auth.startswith("Bearer "):
		return auth.split(" ")[1]
	else:
		raise AuthenticationFailed("Invalid token format")

@database_sync_to_async
def getAvailableTournamentDecorator():
	try:
		tournament = Tournament.objects.get(is_available=True)
		return tournament
	except Exception:
		return None

@database_sync_to_async
def linkRoundToTournamentDecorator(rnd, tournament):
	rnd.tournament = tournament
	rnd.save()

@database_sync_to_async
def getUserDecorator(username):
	try:
		user = User.objects.get(username=username)
		return user
	except Exception:
		return None

@database_sync_to_async
def createRoundDecorator(round_number):
	try:
		rnd = Round.objects.create(round_number=round_number)
		return rnd
	except Exception:
		return None

@database_sync_to_async
def createTournamentDecorator(tournament_id, current_round,gameSettings):
	try:
		tournament = Tournament.objects.create(
			nb_players=1,
			tournament_id=tournament_id,
			tournament_name=f"tournament_{tournament_id}",
			current_round=current_round,
			settings=gameSettings
		)
		return tournament
	except Exception:
		return None

@database_sync_to_async
def createGameDecorator(game_id, player1, player2, tournament, gameSettings, rnd):
	try:
		game = Game.objects.create(
			game_id=game_id,
			game_name=f"game_{game_id}",
			is_available=False,
			is_active=True,
			player1=player1,
			player2=player2,
			is_tournament_game=True,
			tournament=tournament,
			settings = gameSettings,
			round_tournament=rnd		
		)
		return game
	except Exception:
		return None
	

@database_sync_to_async
def addPlayerToRoundDecorator(rnd, player):
	try:
		rnd.players.add(player)
		return True
	except Exception:
		return False

@database_sync_to_async
def addPlayerToTournamentDecorator(tournament, player):
	try:
		tournament.players.add(player)
		return True
	except Exception:
		return False
@database_sync_to_async
def addRoundToTournamentDecorator(tournament, rnd):
	tournament.current_round = rnd


@database_sync_to_async
def getTournamentDecorator(tournament_id):
	try:
		tournament = Tournament.objects.get(tournament_id=tournament_id)
		return tournament
	except Exception:
		return None

@database_sync_to_async
def getTournamentRoundsDecorator(tournament):
	try:
		rounds = list(tournament.rounds.all())
		return rounds
	except Exception:
		return None

@database_sync_to_async
def getLosersInRoundDecorator(rnd):
	try:
		losers = list(rnd.losers.all())
		return losers
	except Exception:
		return None

@database_sync_to_async
def getWinnersInRoundDecorator(rnd):
	return list(rnd.winners.all())

@database_sync_to_async
def getRoundGamesDecorator(rnd):
	try:
		games = list(rnd.games.all())
		return games
	except Exception:
		return None

@database_sync_to_async
def getTournamentPlayersDecorator(tournament):
	try:
		players = list(tournament.players.all())
		return players
	except Exception:
		return None

@database_sync_to_async
def getRoundPlayersDecorator(rnd):
	try:
		players = list(rnd.players.all().order_by('username'))
		return players
	except Exception:
		return None

@database_sync_to_async
def getActiveTournamentDecorator():
	tournament = Tournament.objects.filter(is_active=True).first()
	if tournament is None:
		return None
	else:
		return tournament
	
@database_sync_to_async
def getCurrentRound(tournament):
	return tournament.current_round

@database_sync_to_async
def removePlayerFromRound(rnd, player):
	rnd.players.remove(player)

@database_sync_to_async
def removePlayerToTournamentDecorator(tournament, player):
	tournament.players.remove(player)

@database_sync_to_async
def isOppenentReadyDecorator(opponent):
	opps = User.objects.get(id=opponent)
	if (opps.tournament_status == "Ready"):
		return True
	else:
		return False
@database_sync_to_async
def changeTournamentStatus(user, opponent, status):
	if opponent != "":
		opps =  User.objects.get(id=opponent)
		opps.tournament_status = status
		opps.save()
	user.tournament_status = status
	user.save()


@database_sync_to_async
def getOpponent(user, rnd):
	prev = ''
	next = 0
	i = 0
	players = list(rnd.players.order_by('username'))
	for player in players:
		if next == 1:
			return player.id
		if (player.id == user.id):
			if i % 2 == 1:
				return prev
			else:
				next = 1
		i = i + 1
		prev = player.id
		
	

@database_sync_to_async
def changeGameId(round,user, opponent):
	for game in round.games.all():
		if (user.username == game.player1.username or user.username == game.player2.username):
			user.game_id = game.game_id
			user.save()
			opps =  User.objects.get(id=opponent)
			opps.game_id = game.game_id
			opps.save()


@database_sync_to_async
def getOldRound(tournament):
	return tournament.rounds.get(round_number=2)

@database_sync_to_async
def changeDisplayName(user, new_display_name):
	user.display_name = new_display_name
	user.save()

@database_sync_to_async
def checkDisplayName(tournament, new_display_name):
	return not tournament.players.filter(display_name=new_display_name).exists()

@database_sync_to_async
def changeTournamentSettings(tournament, player1, player2):
	settings = tournament.settings or {}

	if isinstance(settings, str):
		settings = json.loads(settings)

	settings["player1"] = player1
	settings["player2"] = player2
	tournament.settings = settings
	tournament.save()
