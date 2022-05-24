# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 16:06:27 by ebarguil          #+#    #+#              #
#    Updated: 2022/03/31 17:05:24 by ebarguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC		=	ft_putchar_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_split_lib.c \
			ft_split_add.c \
			ft_strjoin.c \
			ft_strjoin_lib.c \
			ft_strjoin_n.c \
			ft_strlen.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strndup.c \
			ft_strdup_cut.c \
			ft_strstr.c \
			ft_bzero.c \
			ft_atoi.c \
			ft_itoa.c \
			gnl.c \

OBJ		=	$(SRC:.c=.o)

N		=	norminette

CC		=	gcc

CF		=	-Wall -Wextra -Werror

RM		=	rm -rf

all		:	$(NAME)

.c.o	:
			$(CC) $(CF) -c $< -o $(<:.c=.o)

$(NAME)	:	$(OBJ)
			ar rcs $(NAME) $(OBJ)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

n		:
			$(N)

.PHONY	:	all clean fclean re n
