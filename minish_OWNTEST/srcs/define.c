/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:30:10 by ebarguil          #+#    #+#             */
/*   Updated: 2022/04/01 18:23:29 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(t_adm *adm, t_elm *elm)
{
	int	fd;
	int	i;

	i = -1;
	while (adm->pth[++i])
	{
		elm->exe = ft_strjoin_lib(adm->pth[i], elm->str);
		if (elm->exe == NULL)
			return (ft_perror("is_command", -1));
		fd = open(elm->exe, O_DIRECTORY);
		if (!access(elm->exe, F_OK) && !access(elm->exe, X_OK) && fd == -1)
			return (1);
		if (fd > 0)
			close(fd);
		free(elm->exe);
		elm->exe = NULL;
	}
	return (0);
}

int	is_builtins(t_elm *elm, char **buil)
{
	int	i;

	i = -1;
	elm->exe = NULL;
	while (buil[++i])
		if (!ft_strcmp(elm->str, buil[i]))
			return (1);
	return (0);
}

void	is_file(t_elm *elm)
{
	int	fd;

	if (access(elm->str, F_OK))
		return ;
	fd = open(elm->str, O_DIRECTORY);
	if (fd == -1)
		elm->t = 'f';
	else
		elm->t = 'd';
	if (fd > 0)
		close(fd);
	return ;
}

int	ft_define_type(t_adm *adm, t_elm *elm)
{
	int		x;

	while (elm != NULL)
	{
		x = 0;
		if (is_builtins(elm, adm->buil))
			elm->t = 'b';
		if (adm->pth && elm->t != 'b')
		{
			x = is_command(adm, elm);
			if (x == -1)
				break ;
			if (x == 1)
				elm->t = 'c';
		}
		if (elm->prev && (ft_strchr(elm->prev->t, "cbo")) && elm->str[0] == '-')
			elm->t = 'o';
		if (elm->t != 'b' && elm->t != 'c' && elm->t != 'o')
			is_file(elm);
		elm = elm->next;
	}
	if (x == -1)
		return (1);
	return (0);
}
