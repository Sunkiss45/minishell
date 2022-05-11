/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:06:16 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/06 15:06:50 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_elm	*ft_start_here(t_adm *adm) //ici OK a rassembler avec ft_count_fd !!
// {
// 	t_elm	*now;

// 	now = adm->head;
// 	if (adm->i != 0)
// 	{
// 		now = adm->head;
// 		while (now != NULL && adm->i != adm->p && now->t != '|')
// 			now = now->next;
// 	}
// 	return (now);
// }

int	ft_count_fd(t_adm *adm)
{
	int		count_fd;
	t_elm	*now;

	now = adm->head;
	if (adm->i != 0)
	{
		now = adm->head;
		while (now != NULL && adm->i != adm->p && now->t != '|')
			now = now->next;
	}
	count_fd = 0;
	while (now != NULL && now->t != '|')
	{
		if (now->t == 'f')
			count_fd++;
		now = now->next;
	}
	return (count_fd);
}

int	ft_count_op(t_elm *now)
{
	int	op;

	op = 0;
	while (now != NULL)
	{
		if (ft_strchr(now->t, "cbo"))
			op++;
		if (now->t == '|')
			break ;
		now = now->next;
	}
	return (op);
}

char	**ft_create_exec(t_elm *now)
{
	char	**exec;
	int		op;
	int		i;

	op = ft_count_op(now);
	if (op != 0)
		exec = malloc(sizeof(char *) * (op + 1));
	while (now != NULL)
	{
		if (now->t == 'c' || now->t == 'b')
			break ;
		now = now->next;
	}
	i = -1;
	while (now != NULL && ++i != -1)
	{
		if (now->t == 'c')
			exec[i] = now->exe;
		if (now->t == 'b')
			exec[i] = now->str;
		if (now->t == 'o')
			exec[i] = now->str;
		if (!ft_strchr(now->t, "cbo"))
			break ;
printf(GREEN"exec[%d] = [%s]"RESET"\n", i, exec[i]);
		now = now->next;
	}
	if (now == NULL)
		i++;
	if (op != 0)
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

void	ft_pointer_pip(t_pip *pip, t_adm *adm)
{
	if (!adm->piph)
	{
		adm->piph = pip;
		adm->pipt = pip;
		pip->next = NULL;
		pip->prev = NULL;
	}
	else
	{
		pip->prev = adm->pipt;
		adm->pipt->next = pip;
		pip->next = NULL;
		adm->pipt = pip;
	}
	pip->exec = NULL;
	pip->t = '\0';
	pip->pass = 0;
	pip->fd_count = ft_count_fd(adm);
	pip->fd_out = -2;
}
