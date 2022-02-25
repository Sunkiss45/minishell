/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:09:45 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/25 21:40:27 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <curses.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../Libft/libft.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

typedef struct s_elm
{
	char			*str;
	char			t;
	struct s_elm	*next;
	struct s_elm	*prev;
}	t_elm;

typedef struct s_dat
{
	int		*ind;
	int		i;
	char	c;
	char	*arg;
	int		x;
}	t_dat;

typedef struct s_adm
{
	char			**ev;
	struct s_elm	*head;
	struct s_elm	*tail;
	struct s_dat	*dat;
}	t_adm;

/* ///// srcs/quote.c ///// */

int	ft_chk_quote(t_adm *adm);

/* ///// srcs/list.c ///// */

int	ft_init_list(char *arg, t_adm *adm);

#endif
