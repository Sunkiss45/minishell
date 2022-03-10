/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:40:43 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/09 16:41:42 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (x);
}
