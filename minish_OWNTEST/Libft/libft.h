/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:50:54 by ebarguil          #+#    #+#             */
/*   Updated: 2021/12/20 10:37:32 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

# define BUFFER_SIZE 1024

/*
 * === ft_put === *
 */

void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

/*
 * === ft_split === *
 */

char	**ft_split(char *str, char *charset);
char	**ft_split_add(char *str, char *charset);

/*
 * === ft_strjoin === *
 */

char	*ft_strjoin(int size, char **strs, char *sep);
char	*ft_strjoin_lib(char *s1, char *s2);

/*
 * === ft_strlen === *
 */

int		ft_strlen(char *s);

/*
 * === get_next_line === *
 */

typedef struct s_gnl
{
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;
	int			r;
	int			i;
	int			j;
}	t_gnl;

char	*gnl(int fd);

#endif
