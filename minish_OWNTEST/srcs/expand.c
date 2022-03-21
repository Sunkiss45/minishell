/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:06:08 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/21 16:20:18 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_exp(char **ev, char *buf)
{
	char	evc[BUF_S];
	int		i;
	int		y;

	i = -1;
	while (ev[++i])
	{
		y = -1;
		ft_bzero(evc, BUF_S);
		while (ev[i][++y] != '=')
			evc[y] = ev[i][y];
		if (ft_strncmp(buf, evc, ft_strlen(evc)) == 0)
			return (i);
	}
	return (-1);
}

char	*ft_take_exp(t_adm *adm, char *str, int *d)
{
	char	buf[BUF_S];
	char	*ret;
	int		x;
	int		i;

	i = 0;
	ft_bzero(buf, BUF_S);
	while ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)
		|| (str[i] >= 48 && str[i] <= 57) || str[i] == 95)
	{
		buf[i] = str[i];
		i++;
	}
	*d += i;
	x = ft_check_exp(adm->ev, buf);
	if (x == -1)
	{
		ret = malloc(sizeof(char) * 1);
		ret[0] = '\0';
		return (ret);
	}
	ret = ft_strdup(&adm->ev[x][i + 1]);
	return (ret);
}

/* c nôté */

int	ft_cut_exp(char **new, t_adm *adm, t_elm *elm, int *i)
{
	char	*tmp;

	tmp = elm->str;
	new[0] = ft_strndup(elm->str, *i);
	if (new[0] == NULL)
		return (1);
	new[1] = ft_take_exp(adm, &elm->str[++*i], i);
	if (new[1] == NULL)
		return (1);
	new[2] = ft_strdup(&elm->str[*i]);
	if (new[2] == NULL)
		return (1);
	elm->str = ft_strjoin(3, new, "");
	expand_free(new, 0);
	free(tmp);
	return (0);
}

int	ft_parse_exp(t_adm *adm, t_elm *elm)
{
	char	*new[3];
	int		i;

	i = -1;
	new[0] = NULL;
	new[1] = NULL;
	new[2] = NULL;
	while (++i < ft_strlen(elm->str) && elm->str[i])
	{
		if (elm->str[i] == '$')
			if (ft_cut_exp(new, adm, elm, &i))
				return (expand_free(new, 1));
		new[0] = NULL;
		new[1] = NULL;
		new[2] = NULL;
	}
	return (expand_free(new, 0));
}

int	ft_expand(t_adm *adm, t_elm *elm)
{
	adm->p = adm->p;
	while (elm != NULL)
	{
		if (elm->t == '\0' || elm->t == '\"')
			if (ft_parse_exp(adm, elm))
				return (ft_perror("ft_parse_ext", 1));
		elm = elm->next;
	}
	return (0);
}
