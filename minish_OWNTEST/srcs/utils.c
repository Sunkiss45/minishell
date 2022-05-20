/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:13:14 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/15 14:15:11 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	printf("Reception de SIGINT (CTRL C) [%d] => nv prompt\n", sig);
	ft_putstr_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

int	ft_get_path(t_adm *adm)
{
	t_env	*ev;

	ev = adm->envh;
	while (ev != NULL)
	{
		if (!ft_strncmp(ev->var, "PATH", 4))
		{
			adm->pth = ft_split_add(ev->val, ":");
			break ;
		}
		ev = ev->next;
	}
	if (errno != 0 && adm->pth == NULL)
		return (1);
	return (0);
}

int	ft_perror(char *s, int x)
{
	perror(s);
	errno = 0;
	return (x);
}
