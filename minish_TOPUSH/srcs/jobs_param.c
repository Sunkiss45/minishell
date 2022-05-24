/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:44:09 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/21 15:44:29 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_save_param(t_elm *now)
{
	char	*param;
	char	*tmp;
	int		i;

	param = NULL;
	while (now != NULL && ft_strchr(now->t, "cbo"))
		now = now->next;
	i = -1;
	while (now != NULL && !ft_strchr(now->t, "><|ah") && ++i != -1)
	{
		if (i)
		{
			tmp = param;
			param = ft_strjoin_lib(tmp, " ");
			free(tmp);
		}
		tmp = param;
		param = ft_strjoin_lib(tmp, now->str);
		if (i)
			free(tmp);
		now = now->next;
	}
	return (param);
}

int	ft_count_op(t_elm *now)
{
	int	op;

	op = 0;
	while (now != NULL && now->t != '|')
	{
		op++;
		now = now->next;
	}
	return (op);
}

t_elm	*ft_go_to_cb(t_elm *now)
{
	t_elm	*sv;

	sv = now;
	while (now != NULL && now->t != '|')
	{
		if (now->t == 'c' || now->t == 'b')
			return (now);
		now = now->next;
	}
	return (sv);
}

char	**ft_create_exec(t_elm *now, int i)
{
	char	**exec;
	int		op;

	op = ft_count_op(now);
	if (op != 0)
		exec = malloc(sizeof(char *) * (op + 1));
	now = ft_go_to_cb(now);
	while (now != NULL && !ft_strchr(now->t, "|<>ah") && ++i != -1)
	{
		if (now->t == 'c')
			exec[i] = now->exe;
		else
			exec[i] = now->str;
		now = now->next;
	}
	if (now == NULL || ft_strchr(now->t, "|<>ah"))
		i++;
	exec[i] = NULL;
	return (exec);
}

char	ft_found_type(t_elm *elm)
{
	char	t;

	t = '\0';
	while (!t && elm && elm->t != '|')
	{
		if (ft_strchr(elm->t, "cb"))
			t = elm->t;
		elm = elm->next;
	}
	while (t && elm && elm->t != '|')
	{
		if (ft_strchr(elm->t, "cb"))
		{
			elm->t = '\0';
			is_file(elm);
		}
		elm = elm->next;
	}
	return (t);
}
