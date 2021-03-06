# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 15:23:29 by ebarguil          #+#    #+#              #
#    Updated: 2022/03/15 14:15:44 by ebarguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INC			=	includes/minishell.h

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -I includes
CFA			=	-fsanitize=address -g3
RM			=	/usr/bin/rm -rf

LIB			=	-L./Libft -lft -L./local/lib -lreadline

vpath %.c srcs

SRC			=	srcs/main.c \
				srcs/env.c \
				srcs/parse.c \
				srcs/list.c \
				srcs/signal.c \
				srcs/jobs_init.c \
				srcs/jobs_param.c \
				srcs/jobs_redir.c \
				srcs/define.c \
				srcs/expand.c \
				srcs/prog.c \
				srcs/prog_bis.c \
				srcs/builtin.c \
				srcs/buil_export.c \
				srcs/utils.c \
				srcs/freelist.c \
				srcs/free.c \

OBJ			=	$(SRC:srcs/%.c=objects/%.o)

all			:	libft obj $(NAME)

$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIB)

libft		:
				$(MAKE) -C Libft

obj			:
				mkdir -p objects

objects/%.o	:	%.c $(INC)
				$(CC) -o $@ -c $< $(CFLAGS)

n			:
				norminette $(SRC)
				norminette $(INC)
				$(MAKE) -C Libft n

clean		:
				$(RM) $(OBJ)
				$(RM) objects
				$(MAKE) -C Libft clean

fclean		:	clean
				$(RM) $(NAME)
				$(MAKE) -C Libft fclean

fsa			:	fclean libft obj $(OBJ)
				$(CC) $(CFLAGS) $(CFA) -o $(NAME) $(SRC) $(LIB)

re			:	fclean all

.PHONY		:	all libft n clean fclean fsa re
