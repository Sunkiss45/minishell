/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:10:18 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/20 14:10:26 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_adm *adm)
{
	t_env	*now;

	now = adm->envh;
	while (now != NULL)
	{
		free(now->var);
		free(now->val);
		free(now->line);
		now = now->next;
		free(adm->envh);
		adm->envh = now;
	}
	adm->envh = NULL;
	adm->envt = NULL;
}

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
