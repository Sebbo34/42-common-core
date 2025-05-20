
SRCS =	ft_action.c \
		ft_atoi.c \
		ft_fork.c \
		ft_start.c \
		ft_think.c \
		ft_time.c \
		philosophers.c \

SRCS_OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

all : ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME} : ${SRCS_OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS_OBJ}

clean :
	rm -f ${SRCS_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean
