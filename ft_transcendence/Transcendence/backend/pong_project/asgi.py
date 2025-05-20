import os
from django.core.asgi import get_asgi_application
from app.routing import websocket_urlpatterns
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack
from app.middleware import WebSocketAuthMiddleware

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'pong_project.settings')

application = ProtocolTypeRouter({
	"http": get_asgi_application(),
	"websocket": WebSocketAuthMiddleware(
		AuthMiddlewareStack(
			URLRouter(websocket_urlpatterns)
		)
	),
})

