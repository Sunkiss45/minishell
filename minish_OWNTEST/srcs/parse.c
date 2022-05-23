/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:42:57 by ebarguil          #+#    #+#             */
/*   Updated: 2022/04/01 18:40:45 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_ope(char x, t_dat *data)
{
	if (data->c != 0)
	{
		data->ind[data->i] = data->c;
		if (data->c == x)
			data->c = 0;
	}
	else if (data->c == 0 && (x == '\'' || x == '\"'
			|| x == '<' || x == '>' || x == '|'))
	{
		data->ind[data->i] = x;
		if (x == '\'' || x == '\"')
			data->c = x;
	}
	else
		data->ind[data->i] = 0;
}

int	ft_parse_quote(char *arg, t_adm *adm, t_dat *dat)
{
	int	x;

	x = 0;
	dat->ind = malloc(sizeof(int) * ft_strlen(arg));
	if (dat->ind == NULL)
		return (1);
	dat->c = 0;
	dat->i = -1;
	while (arg[++dat->i])
		ft_parse_ope(arg[dat->i], dat);
	if (ft_init_list(arg, adm, dat))
	{
		ft_free_list(adm);
		x = 1;
	}
	free(dat->ind);
	return (x);
}

int	ft_job(char *arg, t_adm *adm)
{
	int		x;
	t_elm	*elm;

	if (ft_parse_quote(arg, adm, adm->dat))
		return (1);
	x = 0;
	elm = adm->head;
	adm->i = 0;
	while (elm != NULL && adm->i != adm->p)
	{
		if (!x)
		{
			if (ft_parse_job(adm, elm))
				return (1);
			x = 1;
		}
		if (elm->t == '|')
			x = 0;
		elm = elm->next;
	}
	return (0);
}

int	ft_parse(t_adm *adm)
{
	int		i;
	int		q1;
	int		q2;
	char	*arg;

	i = -1;
	q1 = 0;
	q2 = 0;
	arg = adm->dat->arg;
	if (!arg || !arg[0])
		return (0);
	while (arg[++i])
	{
		if (arg[i] == '\'' && q2 % 2 == 0)
			q1++;
		if (arg[i] == '\"' && q1 % 2 == 0)
			q2++;
	}
	if (q1 % 2 == 0 && q2 % 2 == 0)
		return (ft_job(arg, adm));
	ft_putstr_fd("Quotes invalid !\n", 1);
	return (1);
}
