NAME = ircserv

CC = c++
SRCS = ./main.cpp \
		./src/Server.cpp \
		src/parse.cpp \
		src/channel.cpp \
		src/user.cpp \
		src/PrivMsg.cpp \
		src/utils.cpp \
		src/part.cpp \
		src/kick.cpp \
		src/topic.cpp \
		src/invite.cpp \
		src/nick.cpp \
		src/handleClient.cpp \
		src/join.cpp \
		src/userhost.cpp \
		src/Mode.cpp \
		src/quit.cpp \
		src/authentification.cpp 

OBJS = $(SRCS:.cpp=.o)
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

all : $(NAME)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re