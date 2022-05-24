/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:06:16 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/06 15:06:50 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pointer_pip(t_pip *pip, t_adm *adm)
{
	if (!adm->piph)
	{
		adm->piph = pip;
		adm->pipt = pip;
		pip->next = NULL;
		pip->prev = NULL;
	}
	else
	{
		pip->prev = adm->pipt;
		adm->pipt->next = pip;
		pip->next = NULL;
		adm->pipt = pip;
	}
	pip->exec = NULL;
	pip->t = '\0';
	pip->param = "\0";
	pip->pass = 0;
	pip->fd_out = 500;
}

int	ft_parse_job(t_adm *adm, t_elm *elm)
{
	t_pip	*pip;

	pip = malloc(sizeof(*pip));
	if (pip == NULL)
		return (ft_perror("ft_parse_job", 1));
	ft_pointer_pip(pip, adm);
	pip->t = ft_found_type(elm);
	pip->exec = ft_create_exec(elm, -1);
	pip->param = ft_save_param(elm);
	pip->fd_in = 0;
	pip->fd_out = 1;
	if (ft_redir_in(adm, pip) == -1)
		return (ft_perror("ft_redir_in", 1));
	if (ft_redir_out(adm, pip) == -1)
		return (ft_perror("ft_redir_out", 0));
	adm->i++;
	return (0);
}
