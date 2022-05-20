/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:40:43 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/17 15:57:57 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return_free(char *s, int x)
{
	if (s)
		free(s);
	return (x);
}

int	expand_free(char **new, int x)
{
	int	i;

	i = 0;
	while (i < 3 && new[i])
	{
		free(new[i]);
		i++;
	}
	return (x);
}

int	ft_free(t_adm *adm, char *str, int x)
{
	if (adm->dat)
		free(adm->dat);
	if (adm->pth)
		adm->pth = ft_free_split(adm->pth);
	if (adm->buil)
		adm->buil = ft_free_split(adm->buil);
	if (adm->ev)
		adm->ev = ft_free_split(adm->ev);
	if (adm->head)
		ft_free_list(adm);
	if (adm->envh)
		ft_free_env(adm);
	if (errno != 0 && str)
		perror(str);
	rl_clear_history();
	return (x);
}
