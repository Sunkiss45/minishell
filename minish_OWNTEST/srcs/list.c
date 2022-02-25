/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:27:46 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/25 21:13:29 by ebarguil         ###   ########.fr       */
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
	char	t;

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
	t = str[0];
	if (t == '\'' || t == '\"' || t == '<' || t == '>' || t == '|')
		adm->tail->t = t;
	else
		adm->tail->t = '\0';
	return (0);
}

int	ft_parse_list(char *arg, t_adm *adm, t_dat *dat)
{
	int		k;
	int		b;
	char	buf[1024];

	k = dat->ind[0];
	b = 0;
	ft_bzero(buf, 1024);
	dat->i = 0;
	while (arg[dat->i])
	{
		while (arg[dat->i] && dat->ind[dat->i] == k)
		{
			if (arg[dat->i] == ' ' && k == 0)
				break;
			buf[b++] = arg[dat->i++];
		}
		if (buf[0] != '\0')
		{
			if (ft_create_elm(ft_strdup(buf), adm))
				return (1);
			b = 0;
			ft_bzero(buf, 1024);
		}
		if (arg[dat->i] == ' ')
			dat->i++;
		if (arg[dat->i])
			k = dat->ind[dat->i];
	}
	if (buf[0] != '\0')
		if (ft_create_elm(ft_strdup(buf), adm))
			return (1);
	return (0);
}

int	ft_init_list(char *arg, t_adm *adm)
{
	t_elm	*now;

	adm->head = NULL;
	adm->tail = NULL;
	if (ft_parse_list(arg, adm, adm->dat))
		printf(RED"crash malloc init list"RESET"\n");
	now = adm->head;
//	while (1)
//	{
//		
//	}

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
