/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:42:59 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/20 10:43:33 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pointer_ev(t_env *ev, t_adm *adm)
{
	if (!adm->envh)
	{
		adm->envh = ev;
		adm->envt = ev;
		ev->next = NULL;
	}
	else
	{
		adm->envt->next = ev;
		adm->envt = ev;
		ev->next = NULL;
	}
}

int	ft_split_env(t_env *ev, char *str)
{
	char	*tmp;

	tmp = ft_strchr('=', str);
	ev->var = ft_strndup(str, (tmp - &str[0]));
	if (ev->var == NULL)
		return (1);
	ev->val = ft_strdup(&tmp[1]);
	if (ev->val == NULL)
		return (1);
	return (0);
}

int	ft_create_ev(t_adm *adm, char *str)
{
	t_env	*ev;

	ev = malloc(sizeof(*ev));
	if (ev == NULL)
		return (1);
	ft_pointer_ev(ev, adm);
	ev->line = ft_strdup(str);
	if (ft_split_env(ev, str))
		return (1);
	return (0);
}

void	ft_supr_ev(t_adm *adm, t_env *ev)
{
	t_env	*pov;

	if (!ev)
		return ;
	pov = adm->envh;
	free(ev->var);
	free(ev->val);
	free(ev->line);
	if (ev == adm->envh)
	{
		adm->envh = ev->next;
		free(ev);
		return ;
	}
	while (pov->next != ev)
		pov = pov->next;
	pov->next = ev->next;
	if (ev == adm->envt)
		adm->envt = pov;
	free(ev);
	return ;
}

int	ft_recup_env(char **env, t_adm *adm)
{
	int		i;

	i = 0;
	adm->envh = NULL;
	adm->envt = NULL;
	adm->ev = NULL;
	while (env[i])
	{
		if (ft_create_ev(adm, env[i]))
			return (1);
		i++;
	}
	ft_export("?=0", adm);
	ft_set_shlvl(adm);
	return (0);
}
