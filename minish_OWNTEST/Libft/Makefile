# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 16:06:27 by ebarguil          #+#    #+#              #
#    Updated: 2021/12/20 10:40:56 by ebarguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC		=	ft_putchar_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_split_add.c \
			ft_strjoin.c \
			ft_strjoin_lib.c \
			ft_strlen.c \
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
