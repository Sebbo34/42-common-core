# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:41:57 by dliuzzo           #+#    #+#              #
#    Updated: 2024/04/02 16:51:50 by sbo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

S = src/

I = inc/

L = libft/

O = obj/

D = dep/


CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -g3
#CFLAGS += -fsanitize=address
endif

CFLAGS += -I $I

LDFLAGS = -L$L -lft

SRCS =	$Smain.c \
		$Sinit.c \
		$Slexing.c \
		$Slexing_utils.c \
		$Sutils.c \
		$Sexpand.c \
		$Ssplit_expands.c \
		$Sexpand_utils.c \
		$Sfree.c \
		$Squotes.c \
		$Sutils_2.c \
		$Sskips.c \
		$Sutils_3.c \
		$Sft_echo.c \
		$Sft_env.c \
		$Sft_export.c \
		$Sft_export_utils.c \
		$Sft_pwd.c \
		$Sft_unset.c \
		$Sget_env.c \
		$Spipex.c \
		$Spipex_utils.c \
		$Sft_cd.c \
		$Sget_env_utils.c \
		$Sft_utils.c \
		$Scheck_file.c \
		$Sbuiltins_utils.c \
		$Sft_export_cd.c \
		$Sft_export_parsing.c \
		$Sft_fonc_libft.c \
		$Sft_here_doc.c \
		$Sft_lexbuf_utils.c \
		$Sft_exit.c \
		$Sheredoc_expand.c \
		$Spipex_utils2.c \
		$Ssignal_handler.c \
#		$(addprefix $S, examplefolder/)

RM	=	rm -rf

OBJS =	$(SRCS:$S%=$O%.o)

DEP =	$(SRCS:$S%=$D%.d)

all : lib $(NAME)

$O:
	mkdir -p $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
#	mkdir -p $@
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	mkdir -p $@

$(DEP): | $D

$(DEP): $D%.d: $S%
#	mkdir -p $@
	$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(NAME) : $(OBJS) $(DEP)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) -lreadline

lib:
	make -C $L
	
debug: all

cleanobjs:
	$(RM) $(OBJS) $(O)

lclean:
	make fclean -C libft/

cleandep: 
	$(RM) $(DEP) $(D)

clean: cleanobjs cleandep

fclean : clean lclean
	$(RM) $(NAME)
#	$(RM) $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean lclean re debug lib