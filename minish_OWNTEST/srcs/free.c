/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:40:43 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/04 13:49:20 by ebarguil         ###   ########.fr       */
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
			free(adm->tail);
		}
		else
		{
			free(now->prev->str);
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
	if (adm->buil)
		ft_free_split(adm->buil);
	if (adm->ev)
		ft_free_split(adm->ev);
	if (adm->head)
		ft_free_list(adm);
	if (errno != 0 && str)
		perror(str);
	return (x);
}
