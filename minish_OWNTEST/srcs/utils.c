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

int	ft_get_path(t_adm *adm)
{
	char	**ev;
	int		i;

	adm->pth = NULL;
	ev = adm->ev;
	i = 0;
	while (ev[++i])
		if (ev[i][0] == 'P' && ev[i][1] == 'A' && ev[i][2] == 'T'
			&& ev[i][3] == 'H' && ev[i][4] == '=')
			adm->pth = ft_split_add(&ev[i][5], ":");
	if (errno != 0 && adm->pth == NULL)
		return (1);
// A SUPR
	i = -1;
	while (adm->pth[++i])
		if (adm->pth[i][0] == '/' && adm->pth[i][1] == 'm'
			&& adm->pth[i][2] == 'n' && adm->pth[i][3] == 't'
			&& adm->pth[i][4] == '/')
			adm->pth[i][0] = '\0';
// A SUPR
	return (0);
}

int	ft_perror(char *s, int x)
{
	perror(s);
	errno = 0;
	return (x);
}
