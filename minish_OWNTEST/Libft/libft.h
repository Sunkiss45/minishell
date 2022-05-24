/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:50:54 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/31 17:04:17 by ebarguil         ###   ########.fr       */
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
void	ft_putstr_fd(char *s, int fd);

/*
 * === ft_split === *
 */

char	**ft_split(char *str, char *charset);
char	**ft_split_lib(char *str, char c);
char	**ft_split_add(char *str, char *charset);
void	*ft_free_split(char **strs);

/*
 * === ft_strjoin === *
 */

char	*ft_strjoin(int size, char **strs, char *sep);
char	*ft_strjoin_lib(char *s1, char *s2);
char	*ft_strjoin_n(int size, char **strs);

/*
 * === ft_str === *
 */

int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strchr(char c, char *set);
char	*ft_strdup(char *src);
char	*ft_strndup(char *src, int n);
char	*ft_strdup_cut(char *str, char c);
char	*ft_strstr(char *str, char *to_find);

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
int		ft_strche(char *s, char c, int x);

/*
 * === ft_bzero === *
 */

void	ft_bzero(char *str, int x);

/*
 * === ft_itoa === *
 */

char	*ft_itoa(int n);

/*
 * === ft_atoi === *
 */

int		ft_atoi(const char *str);

#endif
