/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:13:14 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/15 14:15:11 by ebarguil         ###   ########.fr       */
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

void	*ft_set_shlvl(t_adm *adm)
{
	t_env	*ev;
	char	*tmp[2];
	int		shlv;

	ev = adm->envh;
	tmp[0] = NULL;
	while (ev != NULL)
	{
		if (!ft_strcmp(ev->var, "SHLVL"))
			tmp[0] = ft_strdup(ev->val);
		ev = ev->next;
	}
	if (!tmp[0])
		tmp[0] = ft_strdup("0\0");
	shlv = ft_atoi(tmp[0]) + 1;
	free(tmp[0]);
	tmp[0] = ft_itoa(shlv);
	tmp[1] = ft_strjoin_lib("SHLVL=", tmp[0]);
	ft_export(tmp[1], adm);
	return (free(tmp[0]), free(tmp[1]), NULL);
}

int	ft_get_path(t_adm *adm)
{
	t_env	*ev;

	ev = adm->envh;
	if (adm->pth)
		ft_free_split(adm->pth);
	adm->pth = NULL;
	while (ev != NULL)
	{
		if (!ft_strncmp(ev->var, "PATH", 4))
		{
			adm->pth = ft_split_add(ev->val, ":");
			break ;
		}
		ev = ev->next;
	}
	if (errno != 0 && adm->pth == NULL)
		return (1);
	return (0);
}

int	ft_perror(char *s, int x)
{
	perror(s);
	errno = 0;
	return (x);
}
