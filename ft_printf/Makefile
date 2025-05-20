
SRCS =	ft_affiche_hexa.c \
		ft_affiche.c \
		ft_itoa.c \
		ft_printf.c \
		ft_strlcpy.c \
		ft_uputnbr.c


SRCS_OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

all : ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME} : ${SRCS_OBJ}
	ar rc ${NAME} ${SRCS_OBJ} 

clean :
	rm -f ${SRCS_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re