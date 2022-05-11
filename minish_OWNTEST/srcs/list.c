/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:27:46 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/30 15:39:39 by ebarguil         ###   ########.fr       */
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

int	ft_cut_quote(t_adm *adm)
{
	char	*tmp;

	tmp = adm->tail->str;
	adm->tail->str = ft_strdup_cut(adm->tail->str, adm->tail->t);
	free(tmp);
	if (adm->tail->str == NULL)
		return (1);
	return (0);
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
	elm->pip = NULL;
	ft_pointer_elm(elm, adm);
	adm->tail->str = str;
	t = str[0];
	if (t == '\'' || t == '\"' || t == '<' || t == '>' || t == '|')
	{
		adm->tail->t = t;
		if (adm->tail->t == '<' && !ft_strcmp(str, "<<"))
			adm->tail->t = 'h';
		if (t == '|')
			adm->p++;
	}
	else
		adm->tail->t = '\0';
	if ((t == '\'' || t == '\"') && ft_cut_quote(adm))
		return (1);
	return (0);
}

int	ft_parse_list(t_adm *adm, t_dat *dat)
{
	while (dat->arg[dat->i] && dat->ind[dat->i] == dat->k)
	{
		if (dat->arg[dat->i] == ' ' && dat->k == 0)
			break ;
		dat->buf[dat->b++] = dat->arg[dat->i++];
	}
	if (dat->buf[0] != '\0')
	{
		if (ft_create_elm(ft_strdup(dat->buf), adm))
			return (1);
		dat->b = 0;
		ft_bzero(dat->buf, 1024);
	}
	if (dat->arg[dat->i] == ' ')
		dat->i++;
	if (dat->arg[dat->i])
		dat->k = dat->ind[dat->i];
	return (0);
}

int	ft_init_list(char *arg, t_adm *adm, t_dat *dat)
{
	dat->k = dat->ind[0];
	dat->b = 0;
	ft_bzero(dat->buf, BUF_S);
	dat->i = 0;
	adm->p = 1;
	while (arg[dat->i])
		if (ft_parse_list(adm, adm->dat))
			return (1);
	if (dat->buf[0] != '\0')
		if (ft_create_elm(ft_strdup(dat->buf), adm))
			return (1);
	if (ft_define_type(adm, adm->head))
		return (1);
	if (ft_expand(adm, adm->head))
		return (1);
	return (0);
}
