from rest_framework import serializers
from django.contrib.auth.password_validation import validate_password
from .models import *
from app import utilsLogin
from django.contrib.auth import authenticate
from rest_framework_simplejwt.serializers import TokenObtainPairSerializer
from rest_framework_simplejwt.tokens import RefreshToken


class UserSerializer(serializers.ModelSerializer):
	class Meta: #to configure serialization options
		model = User #which model class this serializer is linked to
		fields = ["username", "email", "password", "display_name", "is_online", "avatar", "nb_games", "total_wins", "total_losses"] #which fields from the model class need to be included here
		extra_kwargs = {"password": {"write_only": True}} #to add options to fields: here password can only be written in the requests but never in responses

	def validate_email(self, email):
		email_name, domain_name = email.strip().rsplit("@", 1)
		domain = domain_name.lower()
		if not self.instance and domain == "student.42.fr":
			raise serializers.ValidationError("@student.42.fr email adress are not allowed for standard registration")
		return f"{email_name}@{domain}"

	def create(self, validated_data):
		password = validated_data.pop("password")
		user = User(**validated_data)
		user.username = user.username.strip() #to clean useless spaces
		user.email = self.validate_email(user.email) #to put domain name in lowercase to avoid duplicates + removing spaces
		try:
			validate_password(password, user)
		except Exception as e:
			raise serializers.ValidationError({"password": list(e.messages)}) #to verify password is secured (long enough etc.)
		user.set_password(password) #hashing for database
		user.save() #saves user in database
		return user
	
	def update(self, instance, validated_data):
		if "email" in validated_data:
			email = self.validate_email(validated_data["email"])
			if User.objects.filter(email=email).exclude(id=instance.id).exists():
				raise serializers.ValidationError({"email": "This email is already in use"})
			instance.email = email
		if "username" in validated_data:
			username = validated_data["username"]
			if User.objects.filter(username=username).exclude(id=instance.id).exists():
				raise serializers.ValidationError({"username": "This username is already in use"})
			instance.username = username
		instance.display_name = validated_data.get("display_name", instance.display_name)
		instance.avatar = validated_data.get("avatar", instance.avatar)
		instance.save()
		return instance


class User42Serializer(serializers.ModelSerializer):
	class Meta:
		model = User
		fields = ["username", "avatar"]

	def update(self, instance, validated_data):
		if "username" in validated_data:
			username = validated_data["username"].strip()
			if User.objects.filter(username=username).exclude(id=instance.id).exists():
				raise serializers.ValidationError({"username": "This username is already in use."})
			instance.username = username
		if "avatar" in validated_data:
			instance.avatar = validated_data["avatar"]

		instance.save()
		return instance


class UserLoginSerializer(serializers.Serializer):
	username = serializers.CharField(write_only=True) #can be sent in the request but prevents exposing the username in API responses
	password = serializers.CharField(write_only=True) #not sent in the request but included in the API response

	def validate(self, data):
		user = authenticate(username=data["username"].strip(), password=data["password"])
		if not user:
			raise serializers.ValidationError("Invalid username/password.")
		user.is_online = True
		user.save()
		return {"user": user}


class GameHistorySerializer(serializers.ModelSerializer):
	player1 = serializers.CharField(source="player1.username")
	player2 = serializers.CharField(source="settings.player2", allow_null=True)
	winner = serializers.CharField(source="winner.username", allow_null=True)

	class Meta:
		model = Game
		fields = ["player1", "player2", "player1_score", "player2_score", "winner", "date"]


class CustomRefreshToken(RefreshToken):
	@classmethod
	def for_user(cls, user):
		token = super().for_user(user)
		token["username"] = user.username
		return token
