
SRCS =	create_stack.c \
		ft_atoi.c \
		ft_stack_command.c \
		push_swap.c \
		ft_stack_command_b.c \
		push_swap_utils.c \
		ft_pick.c \
		ft_place.c \
		ft_push_sort.c \
		ft_set_pile.c \
		ft_lst.c \
		sort_little.c \
		error_manage.c \

BONUS = checker.c \
		checker_utils.c \
		ft_stack_command_bonus.c \
		get_next_line_utils.c \
		get_next_line.c \
		create_stack.c \
		error_manage.c \
		push_swap_utils.c \
		ft_lst.c \
		ft_atoi.c \

 
SRCS_OBJ = $(SRCS:.c=.o)

SRCS_OBJ_BONUS = ${BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = push_swap

NAME_BONUS = checker

all : ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME} : ${SRCS_OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS_OBJ} 

bonus :	${SRCS_OBJ_BONUS}
		${CC} ${CFLAGS} -o ${NAME_BONUS} ${SRCS_OBJ_BONUS} 

clean :
	rm -f ${SRCS_OBJ} ${SRCS_OBJ_BONUS}

fclean : clean
	rm -f ${NAME} ${NAME_BONUS}

re : fclean all

.PHONY : all clean fclean re