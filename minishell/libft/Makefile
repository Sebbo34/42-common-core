# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 15:36:07 by dliuzzo           #+#    #+#              #
#    Updated: 2024/03/27 16:36:45 by dliuzzo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

_LSRCS =	ft_isalnum.c  ft_isdigit.c  ft_memchr.c  ft_memmove.c \
ft_putendl_fd.c  ft_split.c  ft_striteri.c  ft_strlcpy.c  ft_strncmp.c \
ft_strtrim.c  ft_toupper.c  ft_bzero.c  ft_isalpha.c  ft_isprint.c \
ft_memcmp.c  ft_memset.c  ft_putnbr_fd.c  ft_strchr.c  ft_strjoin.c \
ft_strlen.c  ft_strnstr.c  ft_substr.c  ft_calloc.c  ft_isascii.c  ft_itoa.c \
ft_memcpy.c  ft_putchar_fd.c  ft_putstr_fd.c  ft_strdup.c  ft_strlcat.c  ft_strmapi.c \
ft_strrchr.c  ft_tolower.c ft_strsub.c ft_lstadd_back.c ft_lstlast.c ft_lstadd_front.c ft_lstmap.c \
ft_lstclear.c  ft_lstnew.c ft_lstdelone.c ft_lstsize.c ft_lstiter.c

_SRCS = ft_digit_count_hexa.c ft_digit_count.c \
ft_printf_char.c ft_printf_hexa.c ft_printf_int.c ft_printf_ptr.c ft_printf_str.c \
ft_printf_unsign.c ft_printf.c ft_putchar.c ft_putnbr_hexa.c ft_putnbr_unsigned.c \
ft_putnbr.c \

SRCS_DIR = librairie
LSRCS_DIR = librairie
SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))
LSRCS = $(addprefix $(LSRCS_DIR)/, $(_LSRCS))
SRCO = $(SRCS:.c=.o)
LSRCO = $(LSRCS:.c=.o)
SRCO += $(LSRCO)

FLAG = -Wall -Wextra -Werror
INC = -I includes/

all : $(NAME)

$(NAME) : $(SRCO)
	ar rc $(NAME) $(SRCO)
	ranlib $(NAME)

%.o : %.c
	cc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO)

fclean : clean
	/bin/rm -f $(NAME)

re :
	make fclean
	make