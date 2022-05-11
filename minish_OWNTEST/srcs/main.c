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

int	ft_recup_env(char **env, t_adm *adm)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
		i++;
	tmp = ft_strjoin_n(i, env);
	if (tmp == NULL)
		return (1);
	adm->ev = ft_split_lib(tmp, '\n');
	free(tmp);
	if (adm->ev == NULL)
		return (1);
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
		ft_free_list(adm);
		free(adm->dat->arg);
		errno = 0;
	}
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_adm				adm;

	av = NULL;
	if (ac != 1)
	{
		errno = 2;
		return (ft_perror("minishell", 1));
	}
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
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
