/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:42:57 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/24 16:50:50 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_quote(char x, t_dat *data)
{
	if (data->c != 0)
	{
		data->ind[data->i] = 1;
		if (data->c == x)
			data->c = 0;
	}
	else if (data->c == 0 && (x == '\'' || x == '\"'))
	{
		data->ind[data->i] = 1;
		data->c = x;
	}
	else
		data->ind[data->i] = 0;
}

int	ft_cut_quote(char *arg, t_adm *adm, t_dat *dat)
{
	dat->ind = malloc(sizeof(int) * ft_strlen(arg));
	if (dat->ind == NULL)
		return (1);
	dat->c = 0;
	dat->i = -1;
	while (arg[++dat->i])
		ft_parse_quote(arg[dat->i], dat);
//
	dat->i = -1;
	printf(GREEN"ind = [");
	while (arg[++dat->i])
		printf("%d", dat->ind[dat->i]);
	printf("]"RESET"\n");
//
	ft_init_list(arg, adm); // fct decouper la ligne par 0 et 1 en malloc
// fct decouper chaque ligne par ' ' (hors 1)
	free(dat->ind);
	return (0);
}

int	ft_chk_quote(t_adm *adm)
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
//	printf(GREEN"q1 \' = [%d] | q2 \" = [%d]"RESET"\n", q1, q2);
	if (q1 % 2 == 0 && q2 % 2 == 0)
		return (ft_cut_quote(arg, adm, adm->dat));
	printf(CYAN"please verify your quotes !"RESET"\n");
	return (1);
}
