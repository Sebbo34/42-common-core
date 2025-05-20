NAME		:= megaphone

SRCS		:= megaphone.cpp 
OBJS		:= $(SRCS:.cpp=.o)

SRCS		:= $(addprefix src/,$(SRCS))
OBJS		:= $(addprefix build/,$(OBJS))

CC			:= c++
CFLAGS		:= -Wall -Wextra -Werror -std=c++98
CPPFLAGS	:= -Iinclude

all: $(NAME)

build/%.o: src/%.cpp
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(NAME): $(OBJS)
	$(CC) ${CFLAGS} -o $(NAME) $(OBJS)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
