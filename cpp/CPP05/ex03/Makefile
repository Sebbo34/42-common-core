NAME		:= form

SRCS		:= Form.cpp \
				Bureaucrat.cpp \
				PresidentialPardonForm.cpp \
				RobotomyRequestForm.cpp \
				ShruberryCreationForm.cpp \
				Intern.cpp \
				main.cpp
OBJS		:= $(SRCS:.cpp=.o)

SRCS		:= $(addprefix src/,$(SRCS))
OBJS		:= $(addprefix build/,$(OBJS))

CC			:= c++ -std=c++98
CFLAGS		:= -Wall -Wextra -Werror 
CPPFLAGS	:= -Iinc

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
