from django.db import models
from django.db.models import Q
import random
from django.utils import timezone
from datetime import timedelta
from django.conf import settings
from django.core.validators import MinLengthValidator
from django.contrib.auth.models import AbstractUser
from django.utils import timezone
from asgiref.sync import sync_to_async
from django.core.validators import RegexValidator

username_validator = RegexValidator(
	regex=r'^[a-zA-Z0-9_-]+$',
	message="User names may only contain letters, numbers, hyphens (-) and underscores (_)."
)

class User(AbstractUser):
	login42 = models.CharField(
		unique=False, #default obligatoire sinon erreur peut pas avoir default et unique sinon il faut lui attribue une variable
		verbose_name="Login 42",
		default="temp_login")
	username = models.CharField(
		max_length=20,
		unique=True,
		error_messages={
			'unique': "This username is already in use.",
		},
		validators=[username_validator]
	)
	display_name = models.CharField(
		max_length=30,
		validators=[MinLengthValidator(3)],
		unique=False, #default obligatoire sinon erreur peut pas avoir default et unique sinon il faut lui attribue une variable
		verbose_name="Display Name",
		null=True,
		blank=True
	)
	email = models.EmailField(
		unique=True,
		error_messages={
			'unique': "This email address is already in use"
		},
		null=True, 
		blank=True
	)
	is_online = models.BooleanField(
		default=False,
		verbose_name="Is Online"
	)
	avatar = models.ImageField(
		upload_to="avatars/", 
		null=True, 
		blank=True, 
		default="avatars/default.png",
		verbose_name="Avatar"
	)
	nb_games = models.PositiveIntegerField(
		default=0,
		verbose_name="Number of Games"
	)
	blocked_list = models.JSONField(
		default=list,
		blank=True,
		verbose_name="Blocked list"
	)
	invitations = models.JSONField(
		default=list,
		blank=True,
		verbose_name="Blocked list"
	)
	friends = models.ManyToManyField(
		settings.AUTH_USER_MODEL,
		blank=True, 
		verbose_name="Friends",
		symmetrical=False
	)
	total_wins = models.PositiveIntegerField(
		default=0,
		verbose_name="Wins"
	)
	total_losses = models.PositiveIntegerField(
		default=0,
		verbose_name="Losses"
	)
	game_id = models.CharField(
		max_length=36,
		default ="",
		verbose_name="Game ID"
	)
	tournament_status = models.CharField(
		max_length=36,
		default ="Unregistered",
		verbose_name="Tournament Status"
	)
	total_matches = models.IntegerField(default=0)
	total_ai_matches = models.IntegerField(default=0)
	total_tournaments = models.IntegerField(default=0)

	async def block_user(self, username):
		if username not in self.blocked_list:
			self.blocked_list.append(username)
			await sync_to_async(self.save)()

	async def unblock_user(self, username):
		if username in self.blocked_list:
			self.blocked_list.remove(username)
			await sync_to_async(self.save)()

	async def is_user_blocked(self, username):
		return username in self.blocked_list
	async def get_blocked_list(self):
		return await sync_to_async(list)(self.blocked_list)

	def gamesPlayed(self):
		return Game.objects.filter(Q(player1=self) | Q(player2=self))

	def __str__(self):
		return self.username

class Round(models.Model):
	tournament = models.ForeignKey(
		"Tournament",
		on_delete=models.CASCADE,
		related_name="rounds",
		null=True,   # autorise les valeurs NULL en base de données
		blank=True 
	)
	round_number = models.IntegerField(
		default=1,
		verbose_name="Round Number"
	)
	is_active = models.BooleanField(
		default=False, 
		verbose_name="Is Active"
	)
	is_finished = models.BooleanField(
		default=False, 
		verbose_name="Is finished"
	)
	winners = models.ManyToManyField(
		settings.AUTH_USER_MODEL,
		blank=True,
		related_name="rounds_won",
		verbose_name="Winner in Round" 
	)
	losers  = models.ManyToManyField(
		settings.AUTH_USER_MODEL,
		blank=True,
		related_name="rounds_lost",
		verbose_name="Loser in Round"
	)
	players = models.ManyToManyField(
		settings.AUTH_USER_MODEL,
		blank=True,
		related_name="round_tournament",
		verbose_name="Participant in Round",
	)
	duration = models.DurationField(default=timedelta(minutes=0))

class Tournament(models.Model):
	tournament_id = models.CharField(
		max_length=36, 
		primary_key=True,
		verbose_name="Tournament ID"
	)
	tournament_name = models.CharField(
		unique=True, 
		verbose_name="Tournament Name"
	)
	is_available = models.BooleanField(
		default=True,
		verbose_name="Is Available"
	)
	is_active = models.BooleanField(
		default=False, 
		verbose_name="Is Active"
	)
	is_finished = models.BooleanField(
		default=False, 
		verbose_name="Is finished"
	)
	max_players = models.PositiveIntegerField(
		default=4, 
		verbose_name="Maximum Players"
	)
	nb_players = models.IntegerField(
		default=0,
		verbose_name="Number of Players"
	)
	current_round = models.ForeignKey(
		"Round",
		blank=True,
		null=True,
		on_delete=models.SET_NULL,
		verbose_name="Current Round",
		related_name="current_in_tournament"
	)
	players = models.ManyToManyField(
		settings.AUTH_USER_MODEL,
		blank=True,
		verbose_name="Participants", 
		related_name="pong_tournaments"
	)
	winner = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.SET_NULL,
		null=True,
		blank=True,
		verbose_name="Tournament Winner",
		related_name="tournaments_won"
	)
	settings = models.JSONField(
		default=dict,
		verbose_name="Game Settings",
		null=True,  # Permet d'accepter une valeur NULL
		blank=True 
	)
	duration = models.DurationField(default=timedelta(minutes=0))

	def __str__(self):
		return self.tournament_name

	def isFull(self):
		return self.nb_players == self.max_players
	
class Game(models.Model):
	game_id = models.CharField(
		max_length=36, 
		primary_key=True,
		verbose_name="Game ID"
	)
	game_name = models.CharField(
		unique=True, 
		verbose_name="Game Name"
	)
	nb_players = models.IntegerField(
		default=0,
		verbose_name="Number of Players"
	)
	is_available = models.BooleanField(
		default=True,
		verbose_name="Is Available"
	)
	is_active = models.BooleanField(
		default=False, 
		verbose_name="Is Active"
	)
	is_finished = models.BooleanField(
		default=False, 
		verbose_name="Is finished"
	)
	max_players = models.PositiveIntegerField(
		default=2, 
		verbose_name="Maximum Players"
	)
	player1 = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.SET_NULL,
		verbose_name="Player 1",
		related_name="games_as_player1",
		null=True
	)
	player2 = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.SET_NULL,
		verbose_name="Player 2",
		related_name="games_as_player2",
		null=True
	)
	player1_score = models.IntegerField(
		default=0,
		verbose_name="Score Player 1"
	)
	player2_score = models.IntegerField(
		default=0,
		verbose_name="Score Player 2"
	)
	winner = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.SET_NULL,
		null=True,
		related_name="games_won",
		verbose_name="Game Winner"
	)
	loser = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.SET_NULL,
		null=True,
		related_name="games_lost",
		verbose_name="Game Loser"
	)
	is_tournament_game = models.BooleanField(
		default=False,
		verbose_name="Is A Tournament Game"
	)
	tournament = models.ForeignKey(
		Tournament,
		null=True,
		on_delete=models.CASCADE,
		related_name="games"
	)
	round_tournament = models.ForeignKey(
		Round,
		null=True,
		on_delete=models.CASCADE,
		related_name="games"
	)
	date = models.DateTimeField(auto_now_add=True)
	settings = models.JSONField(
		default=dict,
		verbose_name="Game Settings",
		null=True,  # Permet d'accepter une valeur NULL
		blank=True 
	)
	def __str__(self):
		return f"{self.player1} vs {self.player2} - Winner: {self.winner}"

class AIMatch(models.Model):
	duration = models.DurationField(default=timedelta(minutes=0))

	player = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.CASCADE,
		related_name="ai_matches",
		verbose_name="Player"
	)
	user = models.ForeignKey(
		User,
		on_delete=models.CASCADE
	)
	
	round_nb = models.IntegerField(default=1)
	rounds_won = models.IntegerField(default=0)

	winner = models.ForeignKey(
		settings.AUTH_USER_MODEL,
		on_delete=models.SET_NULL,
		null=True,
		related_name="ai_wins",
		verbose_name="Winner"
	)
	
	def __str__(self):
		if self.winner == self.player:
			return f"{self.user.username} won against AI"
		return f"{self.user.username} lost against AI"
	

class TwoFactorCode(models.Model):
	user = models.OneToOneField(
		settings.AUTH_USER_MODEL,
		on_delete=models.CASCADE,
		related_name="two_factor_code"
	)
	code = models.CharField(
		max_length=6,
		verbose_name="Two Factor Code"
	)
	expiry = models.DateTimeField(
		verbose_name="Expiry Time",
		default = timezone.now() + timedelta(minutes=10)
	)
	
	def generateCode(self):
		self.expiry = timezone.now() + timedelta(minutes=10)
		self.code = str(random.randint(100000, 999999))
		# self.code = str(111111)
		self.save()
