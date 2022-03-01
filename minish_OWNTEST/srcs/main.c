/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:37:03 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/01 16:15:13 by ebarguil         ###   ########.fr       */
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
	adm->dat->x = 1;
	while (adm->dat->x)
	{
		adm->dat->arg = readline("minishell $> ");
		add_history(adm->dat->arg);
		printf(GREEN"arg = [%s]"RESET"\n", adm->dat->arg);
		if (!adm->dat->arg || ft_strcmp(adm->dat->arg, "exit") == 0)
			adm->dat->x = 0;
		if (ft_chk_quote(adm))
			perror("ft_prompt");
		ft_free_list(adm);
		adm->head = NULL;
		adm->tail = NULL;
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
		perror("minishell");
		return (1);
	}
	adm.head = NULL;
	adm.tail = NULL;
	if (ft_recup_env(env, &adm))
		return (ft_free(&adm, "ft_recup_env", 1));
	adm.dat = malloc(sizeof(*adm.dat));
	if (adm.dat == NULL)
		return (ft_free(&adm, "main adm.dat", 1));
	ft_prompt(&adm);
	return (ft_free(&adm, NULL, 0));
}
