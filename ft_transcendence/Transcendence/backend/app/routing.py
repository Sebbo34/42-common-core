from django.urls import re_path
from app.gameConsumers import GameConsumer
from app.tournamentConsumers import TournamentLobbyConsumer
from app.chatConsumers import ChatConsumer
from app.chatConsumers import GsConsumer

websocket_urlpatterns = [
	re_path(r"^ws/game/(?P<game_id>[a-f0-9\-]+)/$", GameConsumer.as_asgi()),
	re_path(r'ws/tournament_lobby/$', TournamentLobbyConsumer.as_asgi()),
	re_path(r'ws/chat/$', ChatConsumer.as_asgi()),
	re_path(r'ws/create_gs/$', GsConsumer.as_asgi()),
]