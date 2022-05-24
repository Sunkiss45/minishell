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

int	g_sig;

int	ft_exit_isa(t_adm *adm)
{
	if (ft_strncmp(adm->dat->arg, "exit", 4) == 0
		&& ft_strlen(adm->dat->arg) > 4)
		write(1, "exit\n", 5);
	if (!adm->dat->arg)
		write(1, "exit\n", 5);
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
		if (ft_strncmp(adm->dat->arg, "exit", 4) == 0 || !adm->dat->arg)
			adm->dat->x = ft_exit_isa(adm);
		if (adm->dat->x)
		{
			r = ft_get_path(adm);
			r = ft_parse(adm);
		}
		if (r)
			ft_perror("ft_prompt", 0);
		if (adm->dat->x && adm->dat->arg[0] && adm->piph)
			ft_execute_prog(adm);
		ft_free_pip(adm);
		ft_free_list(adm);
		free(adm->dat->arg);
		errno = 0;
	}
}

/*void	ft_read_env(t_adm *adm)
{
	t_env	*now;

	now = adm->envh;
	while (now != NULL)
	{
		printf(YELLOW"[%s]\n"GREEN"[%s] [%s]"RESET"\n", now->line, now->var, now->val);
		free(now->var);
		free(now->val);
		now = now->next;
		free(adm->envh);
		adm->envh = now;
	}
}*/

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
	adm.pth = NULL;
	adm.i = 0;
	if (ft_recup_env(env, &adm))
		return (ft_free(&adm, "ft_recup_env", 1));
	adm.dat = malloc(sizeof(*adm.dat));
		adm.buil = ft_split(BUILTINS, " ");
	if (adm.dat == NULL || adm.buil == NULL)
		return (ft_free(&adm, "main adm.dat", 1));
	ft_prompt(&adm);
	return (ft_free(&adm, NULL, 0));
}
