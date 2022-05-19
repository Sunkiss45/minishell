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

void	ft_free_pip(t_adm *adm)
{
	t_pip	*now;

	now = adm->piph;
	while (now != NULL)
	{
		if (now->param)
			free(now->param);
		now = now->next;
		if (now == NULL)
		{
			if (adm->pipt->exec)
				free(adm->pipt->exec);
			free(adm->pipt);
		}
		else
		{
			if (now->prev->exec)
				free(now->prev->exec);
			free(now->prev);
		}
	}
	adm->piph = NULL;
	adm->pipt = NULL;
}

void	ft_free_list(t_adm *adm)
{
	t_elm	*now;

	now = adm->head;
	while (now != NULL)
	{
printf(YELLOW"[%s] | [%c]"RESET"\n", now->str, now->t);
		now = now->next;
		if (now == NULL)
		{
			free(adm->tail->str);
			if (adm->tail->exe)
				free(adm->tail->exe);
			free(adm->tail);
		}
		else
		{
			free(now->prev->str);
			if (now->prev->exe)
				free(now->prev->exe);
			free(now->prev);
		}
	}
	adm->head = NULL;
	adm->tail = NULL;
}

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
	if (errno != 0 && str)
		perror(str);
	rl_clear_history();
	return (x);
}
