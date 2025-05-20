
SRCS =	ft_split.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_substr.c	\
		get_env.c \
		get_next_line.c \
		get_next_line_utils.c \
		pipex.c \
		pipex_utils.c \

SRCS_OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = pipex

all : ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME} : ${SRCS_OBJ} 
	${CC} ${CFLAGS} -o ${NAME} ${SRCS_OBJ} 

clean :
	rm -f ${SRCS_OBJ} ${SRCS_OBJ_BONUS}

fclean : clean
	rm -f ${NAME} ${NAME_BONUS}

re : fclean all

.PHONY : all clean fclean re