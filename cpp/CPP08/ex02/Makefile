NAME		:= ex02

SRCS		:= main.cpp 
OBJS		:= $(SRCS:.cpp=.o)

SRCS		:= $(addprefix src/,$(SRCS))
OBJS		:= $(addprefix build/,$(OBJS))
DEPS        := $(OBJS:.o=.d)

CC			:= c++ -std=c++98
CFLAGS		:= -Wall -Wextra -Werror 
CPPFLAGS	:= -MMD -MP -Iinc

all: $(NAME)

build/%.o: src/%.cpp
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(NAME): $(OBJS)
	$(CC) ${CFLAGS} -o $(NAME) $(OBJS)

-include $(DEPS)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
