import os
from pathlib import Path
from django.core.management.utils import get_random_secret_key
from datetime import timedelta

SECRET_KEY_JWT = os.environ.get("SECRET_KEY_JWT")

OAUTH_CLIENT_ID = os.environ.get("OAUTH_CLIENT_ID")
OAUTH_CLIENT_SECRET = os.environ.get("OAUTH_CLIENT_SECRET")
OAUTH_REDIRECT_URI = os.environ.get("OAUTH_REDIRECT_URI")
OAUTH_AUTH_URL = os.environ.get("OAUTH_AUTH_URL")
OAUTH_TOKEN_URL = os.environ.get("OAUTH_TOKEN_URL")
OAUTH_USER_INFO_URL = os.environ.get("OAUTH_USER_INFO_URL")

REDIRECT_HOME_PAGE = os.environ.get("REDIRECT_HOME")

EMAIL_BACKEND = "django.core.mail.backends.smtp.EmailBackend"
EMAIL_HOST = "smtp.gmail.com"
EMAIL_PORT = 587
EMAIL_USE_TLS = True
EMAIL_HOST_USER = os.getenv("EMAIL_USER")
EMAIL_HOST_PASSWORD = os.getenv("EMAIL_PASSWORD")
DEFAULT_FROM_EMAIL = EMAIL_HOST_USER

AUTH_USER_MODEL = 'app.User'

# Build paths inside the project like this: BASE_DIR / 'subdir'.
BASE_DIR = Path(__file__).resolve().parent.parent

MEDIA_URL = '/media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')

# Quick-start development settings - unsuitable for production
# See https://docs.djangoproject.com/en/5.1/howto/deployment/checklist/

SECRET_KEY = os.getenv('DJANGO_SECRET_KEY', get_random_secret_key())

DEBUG = True

ALLOWED_HOSTS = [
	"localhost",
	"127.0.0.1",
	os.getenv("LOCAL_IP")
]

SECURE_PROXY_SSL_HEADER = ('HTTP_X_FORWARDED_PROTO', 'https')

SESSION_COOKIE_SECURE = False
CSRF_COOKIE_SECURE = True

INSTALLED_APPS = [
	'django.contrib.admin',
	'django.contrib.auth',
	'django.contrib.contenttypes',
	'django.contrib.sessions',
	'django.contrib.messages',
	'daphne',
	'django.contrib.staticfiles',
	'corsheaders',
	'rest_framework',
	'rest_framework.authtoken',
	'rest_framework_simplejwt',
	'rest_framework_simplejwt.token_blacklist',
	'channels',
	'app',
]

MIDDLEWARE = [
	'corsheaders.middleware.CorsMiddleware',
	'django.middleware.security.SecurityMiddleware',
	'django.contrib.sessions.middleware.SessionMiddleware',
	'django.middleware.common.CommonMiddleware',
	'django.middleware.csrf.CsrfViewMiddleware',
	'django.contrib.auth.middleware.AuthenticationMiddleware',
	'django.contrib.messages.middleware.MessageMiddleware',
	'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

REST_FRAMEWORK = {
	'DEFAULT_RENDERER_CLASSES': [
		'rest_framework.renderers.JSONRenderer',
	],
	'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.PageNumberPagination',
	'PAGE_SIZE': 10,
}

AUTH_USER_MODEL = 'app.User'

ROOT_URLCONF = 'pong_project.urls'

TEMPLATES = [
	{
		'BACKEND': 'django.template.backends.django.DjangoTemplates',
		'DIRS': [os.path.join(BASE_DIR, 'templates')],
		'APP_DIRS': True,
		'OPTIONS': {
			'context_processors': [
				'django.template.context_processors.debug',
				'django.template.context_processors.request',
				'django.contrib.auth.context_processors.auth',
				'django.contrib.messages.context_processors.messages',
			],
		},
	},
]

WSGI_APPLICATION = 'pong_project.wsgi.application'

# Database
# https://docs.djangoproject.com/en/5.1/ref/settings/#databases

DATABASES = {
	'default': {
		'ENGINE': 'django.db.backends.postgresql',
		'NAME': os.getenv('POSTGRES_DB'),
		'USER': os.getenv('POSTGRES_USER'),
		'PASSWORD': os.getenv('POSTGRES_PASSWORD'),
		'HOST': os.getenv('POSTGRES_HOST'),
		'PORT': os.getenv('POSTGRES_PORT'),
	}
}

# Password validation
# https://docs.djangoproject.com/en/5.1/ref/settings/#auth-password-validators

AUTH_PASSWORD_VALIDATORS = [
	{
		'NAME': 'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',
	},
	{
		'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',
		'OPTIONS': {'min_length': 8}
	},
	{
		'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',
	},
	{
		'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',
	},
]

AUTHENTICATION_BACKENDS = [
	'django.contrib.auth.backends.ModelBackend',
]

PASSWORD_HASHERS = [
	'django.contrib.auth.hashers.PBKDF2PasswordHasher',
	'django.contrib.auth.hashers.BCryptSHA256PasswordHasher',
	'django.contrib.auth.hashers.ScryptPasswordHasher',
]

ASGI_APPLICATION = "pong_project.asgi.application"

CHANNEL_LAYERS = {
	"default": {
		"BACKEND": "channels_redis.core.RedisChannelLayer",
		"CONFIG": {
			"hosts": [("redis", 6379)],
		},
	},
}

SIMPLE_JWT = {
	'ALGORITHM': 'HS256',
	'ACCESS_TOKEN_LIFETIME': timedelta(days=1),
	'REFRESH_TOKEN_LIFETIME': timedelta(days=1),
	'ROTATE_REFRESH_TOKENS': True,
	'BLACKLIST_AFTER_ROTATION': True,
	'UPDATE_LAST_LOGIN': False,
	'SIGNING_KEY': SECRET_KEY_JWT,
	'AUTH_COOKIE': 'access_token',
	'AUTH_COOKIE_REFRESH': 'refresh_token',
	'AUTH_COOKIE_SECURE': True,
	'AUTH_COOKIE_HTTP_ONLY': True,
	'AUTH_COOKIE_SAMESITE': 'Lax',
	'JTI_CLAIM': 'jti',
	'TOKEN_OBTAIN_SERIALIZER': 'app.serializers.CustomTokenObtainPairSerializer',
	'TOKEN_TYPE_CLAIM': 'token_type',
	'TOKEN_USER_CLASS': 'rest_framework_simplejwt.models.TokenUser',
}

# Internationalization
# https://docs.djangoproject.com/en/5.1/topics/i18n/

LANGUAGE_CODE = 'en-us'
TIME_ZONE = 'UTC'
USE_I18N = True
USE_TZ = True

# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/5.1/howto/static-files/

STATIC_URL = '/static/'

# Default primary key field type
# https://docs.djangoproject.com/en/5.1/ref/settings/#default-auto-field

DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'

CORS_ALLOW_ALL_ORIGINS = False

CORS_ALLOWED_ORIGINS = [
	"https://localhost",	
	os.environ.get("WEB_SERVICE_URL"),
	os.environ.get("REDIRECT_LOCAL_HOME"),
	os.environ.get("REDIRECT_HOME"),
	os.environ.get("URL_API")
]

CORS_ALLOW_CREDENTIALS = True  # Permet d'envoyer des cookies avec la requête
CORS_ALLOW_METHODS = ["GET", "POST", "OPTIONS", "PUT", "DELETE"]
CORS_ALLOW_HEADERS = [ "Content-Type"]

LOGIN_URL = '/login/'  
