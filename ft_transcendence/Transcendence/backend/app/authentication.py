from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import UntypedToken
from rest_framework.exceptions import AuthenticationFailed
from app import utilsLogin
from app.models import User

class CookieJWTAuthentication(JWTAuthentication):
	def authenticate(self, request):
		access_token = request.COOKIES.get("access_token")
		if not access_token:
			return None
		try:
			# On décode le token JWT pour le valider
			UntypedToken(access_token)  # Cela va lever une exception si le token est invalide
			user = self.get_user(access_token)
			if not user or not user.is_active:
				return None
		except Exception as e:
			return None

		# Si le token est valide, on continue à l'authentifier et renvoie l'utilisateur
		return (user, access_token)

	def get_user(self, access_token):
		try:
			user_info = utilsLogin.decodeJWT(access_token)
			if (user_info is None):
				return None
			user = User.objects.get(username=user_info["username"])
			return user
		except KeyError:
			return None
