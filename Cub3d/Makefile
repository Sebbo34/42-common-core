NAME		:= cub3D

SRCS		:=	main.c \
				column.c \
				scene.c \
				map.c \
				map_from_strs.c \
				assets.c \
				rect.c \
				window.c \
				ray.c \
				ray_hit_walls.c \
				ray_hit_rect_inside.c \
				ray_hit_rect_outside.c \
				player.c \
				event.c \
				get_next_line.c \
				color.c \
				parsing.c \
				str_array.c \
				image.c
OBJS		:= $(SRCS:.c=.o)

SRCS		:= $(addprefix sources/,$(SRCS))
OBJS		:= $(addprefix build/,$(OBJS))

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -Iinclude -Iminilibx-linux
LDFLAGS		:= -Lminilibx-linux -lmlx -lm -lX11 -lXext

all: $(NAME)

build/%.o: sources/%.c
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(NAME): $(OBJS) minilibx-linux/libmlx.a
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

minilibx-linux/libmlx.a:
	$(MAKE) -C minilibx-linux

clean:
	$(MAKE) -C minilibx-linux clean
	rm -rf build

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re