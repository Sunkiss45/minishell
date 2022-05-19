/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:37:03 by ebarguil          #+#    #+#             */
/*   Updated: 2022/04/01 15:42:27 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_recup_env(char **env, t_adm *adm)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	tmp = ft_strjoin_n(i, env);
// 	if (tmp == NULL)
// 		return (1);
// 	adm->ev = ft_split_lib(tmp, '\n');
// 	free(tmp);
// 	if (adm->ev == NULL)
// 		return (1);
// 	return (0);
// }

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
	ev->line = str;
	if (ft_split_env(ev, str))
		return (1);
	return (0);
}

int	ft_recup_env(char **env, t_adm *adm)
{
	int		i;

	i = 0;
	adm->envh = NULL;
	adm->envt = NULL;

	while (env[i])
	{
		if (ft_create_ev(adm, env[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_prompt(t_adm *adm)
{
	int	r;

	adm->dat->x = 1;
	r = 0;
	while (adm->dat->x)
	{
		adm->dat->arg = readline("minishell $> ");
		add_history(adm->dat->arg);
printf(GREEN"arg = [%s]"RESET"\n", adm->dat->arg);
		if (!adm->dat->arg || ft_strcmp(adm->dat->arg, "exit") == 0)
			adm->dat->x = 0;
		if (adm->dat->x)
			r = ft_parse(adm);
		if (r)
			ft_perror("ft_parse", 0);
		if (adm->dat->x && adm->dat->arg[0] && adm->piph)
			ft_execute_prog(adm);
		ft_free_pip(adm);
		ft_free_list(adm);
		free(adm->dat->arg);
		errno = 0;
	}
}

int	main(int ac, char **av, char **env)
{
	t_adm	adm;

	av = NULL;
	if (ac != 1)
	{
		errno = 2;
		return (ft_perror("minishell", 1));
	}
	ft_signal();
	adm.head = NULL;
	adm.tail = NULL;
	adm.piph = NULL;
	adm.pipt = NULL;
	adm.i = 0;
	if (ft_recup_env(env, &adm))
		return (ft_free(&adm, "ft_recup_env", 1));
	if (ft_get_path(&adm))
		return (ft_perror("ft_get_path", 1));
	adm.dat = malloc(sizeof(*adm.dat));
		adm.buil = ft_split(BUILTINS, " ");
	if (adm.dat == NULL || adm.buil == NULL)
		return (ft_free(&adm, "main adm.dat", 1));
	ft_prompt(&adm);
	return (ft_free(&adm, NULL, 0));
}
