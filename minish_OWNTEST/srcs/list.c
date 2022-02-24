/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:27:46 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/24 18:26:41 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pointer_elm(t_elm *elm, t_adm *adm)
{
	if (!adm->head)
	{
		adm->head = elm;
		adm->tail = elm;
		elm->next = NULL;
		elm->prev = NULL;
	}
	else
	{
		elm->prev = adm->tail;
		adm->tail->next = elm;
		elm->next = NULL;
		adm->tail = elm;
	}
}

int	ft_create_elm(char *str, t_adm *adm)
{
	t_elm	*elm;

	if (str == NULL)
		return (1);
	elm = malloc(sizeof(*elm));
	if (elm == NULL)
	{
		free(str);
		return (1);
	}
	ft_pointer_elm(elm, adm);
	adm->tail->str = str;
	if (str[0] == '\'' || str[0] == '\"')
		adm->tail->t = str[0];
	else
		adm->tail->t = '\0';
	return (0);
}

int	ft_parse_list(char *arg, t_adm *adm)
{
	int		k;
	int		b;
	char	buf[1024];

	k = adm->dat->ind[0];
	b = -1;
	ft_bzero(buf, 1024);
	adm->dat->i = -1;
	while (arg[++adm->dat->i])
	{
		if (adm->dat->ind[adm->dat->i] == k)
			buf[++b] = arg[adm->dat->i];
		else
		{
			k = adm->dat->ind[adm->dat->i];
			if (ft_create_elm(ft_strdup(buf), adm))
				return (1);
			b = -1;
			ft_bzero(buf, 1024);
			buf[++b] = arg[adm->dat->i];
		}
	}
	if (ft_create_elm(ft_strdup(buf), adm))
		return (1);
	return (0);
}

int	ft_init_list(char *arg, t_adm *adm)
{
	t_elm	*now;

	adm->head = NULL;
	adm->tail = NULL;
	ft_parse_list(arg, adm);

	now = adm->head;
	while (now != NULL)
	{
		printf(YELLOW"str = [%s] || t = [%c]"RESET"\n", now->str, now->t);
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
	return (0);
}
