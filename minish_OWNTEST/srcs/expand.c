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

t_env	*ft_check_exp(t_adm *adm, char *buf)
{
	t_env	*ev;

	ev = adm->envh;
	while (ev != NULL)
	{
		if (!ft_strcmp(buf, ev->var))
			return (ev);
		ev = ev->next;
	}
	return (NULL);
}

char	*ft_take_exp(t_adm *adm, char *str, int *y, int *i)
{
	char	buf[BUF_S];
	char	*ret;
	int		x;

	x = 0;
	ft_bzero(buf, BUF_S);
	while (str[x] && ((str[x] >= 65 && str[x] <= 90)
			|| (str[x] >= 97 && str[x] <= 122)
			|| (str[x] >= 48 && str[x] <= 57) || str[x] == 95 || str[x] == 63))
	{
		buf[x] = str[x];
		x++;
	}
	*y += x;
	if (!ft_check_exp(adm, buf))
	{
		*i -= 1;
		ret = malloc(sizeof(char) * 1);
		ret[0] = '\0';
		return (ret);
	}
	ret = ft_strdup(ft_check_exp(adm, buf)->val);
	*i += ft_strlen(ret) - 1;
	return (ret);
}

int	ft_cut_exp(char **new, t_adm *adm, t_elm *elm, int *i)
{
	char	*tmp;
	int		y[1];

	y[0] = i[0];
	tmp = elm->str;
	new[0] = ft_strndup(elm->str, *y);
	if (new[0] == NULL)
		return (1);
	new[1] = ft_take_exp(adm, &elm->str[*y + 1], y, i);
	if (new[1] == NULL)
		return (1);
	new[2] = ft_strdup(&elm->str[++*y]);
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
	while (elm != NULL)
	{
		if (elm->t == '\0' || elm->t == '\"')
			if (ft_parse_exp(adm, elm))
				return (ft_perror("ft_parse_ext", 1));
		elm = elm->next;
	}
	return (0);
}
