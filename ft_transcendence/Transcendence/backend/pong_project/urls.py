from django.contrib import admin
from django.urls import path
from app import views
from django.conf import settings
from django.conf.urls.static import static
from django.views.generic import TemplateView

urlpatterns = [
	path('add-friend/', views.AddFriendView.as_view()),
	path('admin/', admin.site.urls),
	path('code-2fa/', views.Verify2FAView.as_view()),
	path('callback/', views.CallbackView.as_view()),
	path('create_game_without_lobby/', views.GameWithoutLobbyView.as_view()),
	path('create_local_game/', views.GameLocalView.as_view()),
	path('friend-list/', views.FriendsListView.as_view()),
	path('game-info/', views.GameInfoView.as_view()),
	path('game_settings/', views.LocalGameSettingsView.as_view()),
	path('gs_without_lobby/', views.GameSettingsWithoutLobbyView.as_view()),
	path('login/', views.UserLoginView.as_view()),
	path('login/42/', views.UserLogin42View.as_view()),
	path('logout/', views.UserLogoutView.as_view()),
	path('match-history/', views.MatchHistoryView.as_view()),
	path('my_infos/', views.MyInfosView.as_view()),
	path('remove-friend/', views.RemoveFriend.as_view()),
	path('sign-in/', views.UserRegisterView.as_view()),
	path('update-profil/', views.UpdateProfileView.as_view()),
	path('user-profil/', views.UserProfileView.as_view()),
	path('users_profile/', TemplateView.as_view(template_name='index.html')),
	path('social/', views.AllUsersView.as_view())
]

if settings.DEBUG:
	urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
