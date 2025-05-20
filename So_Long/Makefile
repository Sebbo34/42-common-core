
SRCS =	check_map.c \
		checkpath.c \
		creat_struc.c \
		ft_lst.c \
		ft_putnbr_img.c \
		ft_strlen.c \
		get_next_line.c \
		get_next_line_utils.c \
		move.c \
		move_utils.c \
		set_image.c \
		so_long.c \
		sorcier.c \
		sorcier_utils.c \

SRCS_OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = so_long

all : mlx ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME} : ${SRCS_OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS_OBJ} -Lminilibx-linux -Iminilibx-linux -lmlx -lXext -lX11

clean :
	rm -f ${SRCS_OBJ}
	make clean -C ./minilibx-linux

fclean : clean
	rm -f ${NAME}

re : fclean all

mlx :
	make -C ./minilibx-linux

.PHONY : all clean fclean re
