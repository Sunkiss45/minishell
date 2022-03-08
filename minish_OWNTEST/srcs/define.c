/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:30:10 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/07 11:43:29 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(t_adm *adm, t_elm *elm)
{

	return (0);
}

int	is_builtins(t_elm *elm, char **buil)
{
	int	i;

	i = -1;
	while (buil[++i])
		if (!ft_strcmp(elm->str, buil[i]))
			return (1);
	return (0);
}

void	is_file(t_elm *elm)
{
	if (access(elm->str, F_OK))
		return ;
	if (open(elm->str, O_DIRECTORY) == -1)
		elm->t = 'f';
	else
		elm->t = 'd';
	return ;
}

int	ft_define_type(t_adm *adm)
{
	t_elm	*elm;

	if (ft_get_path(adm))
		return (ft_perror("ft_get_path", 1));
	elm = adm->head;
	while (elm != NULL)
	{
		if (is_builtins(elm, adm->buil))
			elm->t = 'b';
		else if (is_command(adm, elm))
			elm->t = 'c';
		// else if (is_option())
		// 	elm->t = 'o';
		if (elm->t != 'b' && elm->t != 'c' && elm->t != 'o')
			is_file(elm);
		elm = elm->next;
	}
	ft_free_split(adm->pth);
	return (0);
}
