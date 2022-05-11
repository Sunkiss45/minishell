/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:09:45 by ebarguil          #+#    #+#             */
/*   Updated: 2022/04/01 17:59:17 by ebarguil         ###   ########.fr       */
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

# define BUILTINS "echo cd pwd export unset env exit"
# define BUF_S 1024
//# define _POSIX_C_SOURCE 200809L // prend en compte le flag O_DIRECTORY

typedef struct s_elm
{
	char			*str;
	char			*exe;
	char			t;
	struct s_pip	*pip;
	struct s_elm	*next;
	struct s_elm	*prev;
}	t_elm;

typedef struct s_pip
{
	char			**exec;
	char			t;
	int				pass;
	int				fd_count;
	int				fd_in[BUF_S];
	int				fd_out;
	struct s_pip	*next;
	struct s_pip	*prev;
}	t_pip;

typedef struct s_dat
{
	char	buf[BUF_S];
	char	c;
	int		*ind;
	int		i;
	int		k;
	int		b;
	char	*arg;
	int		x;
}	t_dat;

typedef struct s_adm
{
	char			**ev;
	char			**buil;
	char			**pth;
	struct s_elm	*head;
	struct s_elm	*tail;
	struct s_pip	*piph;
	struct s_pip	*pipt;
	struct s_dat	*dat;
	int				p;
	int				i;
}	t_adm;

/*
 *	srcs/parse.c 
 */

int		ft_parse(t_adm *adm);

/*
 *	srcs/list.c 
 */

int		ft_init_list(char *arg, t_adm *adm, t_dat *dat);

/*
 *	srcs/jobs.c 
 */

void	ft_pointer_pip(t_pip *pip, t_adm *adm);
char	ft_found_type(t_elm *elm);
char	**ft_create_exec(t_elm *now);

/*
 *	srcs/redir.c 
 */

void	print_pip(t_pip *pip); /// A SUPPR
int		ft_redir_in(t_adm *adm, t_pip *pip);
int 	ft_redir_out(t_adm *adm, t_pip *pip);

/*
 *	srcs/prog.c
 */

int		ft_execute_prog(t_adm *adm);

/*
 *	srcs/define.c
 */

void	is_file(t_elm *elm);
int		ft_define_type(t_adm *adm, t_elm *elm);

/*
 *	srcs/expand.c
 */

int		ft_expand(t_adm *adm, t_elm *elm);

/*
 *	srcs/builtin.c
 */

int		ft_echo(char *s);
void	ft_cd(t_adm *adm, t_elm *elm);
void	ft_pwd(void);
void	ft_export(char *s, t_adm *adm);
void	ft_unset(char *s, t_adm *adm);
void	ft_env(t_adm *adm);

/*
 *	srcs/utils.c
 */

void	handle_sigint(int sig);
int		ft_get_path(t_adm *adm);
int		ft_perror(char *s, int x);

/*
 *	srcs/free.c
 */

void	ft_free_list(t_adm *adm);
int		expand_free(char **new, int x);
int		ft_free(t_adm *adm, char *str, int x);

#endif