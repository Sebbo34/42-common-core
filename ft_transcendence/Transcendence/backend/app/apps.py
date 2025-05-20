#Django app for user management (can be customized)

from django.apps import AppConfig

#BigAutoField used to allow lots of registrations

class UserManagementConfig(AppConfig):
	default_auto_field ='django.db.models.BigAutoField'
	name = 'app'

def ready(self):
	print("app app ready")
