/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:37:03 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/25 22:10:31 by ebarguil         ###   ########.fr       */
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
//	printf(CYAN"[\n%s\n]"RESET"\n", tmp);
	adm->ev = ft_split_lib(tmp, '\n');
	i = 0;
	while (adm->ev[i])
	{
		printf(CYAN"[%s]"RESET"\n", adm->ev[i]);
		if (ft_strcmp(env[i], adm->ev[i]) != 0)
			printf(RED"y'a un blem"RESET"\n");
		else
			printf(GREEN"OK"RESET"\n");
		i++;
	}
	free(tmp);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_adm	adm;
	char	*prompt;

	av = NULL;
	prompt = "minishell $> ";
	if (ac != 1)
	{
		errno = 2;
		perror("minishell");
		return (0);
	}
	if (ft_recup_env(env, &adm))
		return (1);
	adm.dat = malloc(sizeof(*adm.dat));
//	dat = malloc(sizeof(*dat));
//	adm->dat = dat;
	adm.dat->x = 1;
	while (adm.dat->x)
	{
		adm.dat->arg = readline(prompt);
		add_history(adm.dat->arg);
		printf(GREEN"arg = [%s]"RESET"\n", adm.dat->arg);
		if (!adm.dat->arg || ft_strcmp(adm.dat->arg, "exit") == 0
			|| ft_chk_quote(&adm))
			adm.dat->x = 0;
		free(adm.dat->arg);
	}
	free(adm.dat);
	return (0);
}
