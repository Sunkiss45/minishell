/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:37:03 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/24 16:36:30 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	t_adm	adm;
	char	*prompt;

	av = NULL;
	ev = NULL;
	prompt = "minishell $> ";
	if (ac != 1)
	{
		errno = 2;
		perror("minishell");
		return (0);
	}
	adm.dat = malloc(sizeof(*adm.dat));
//	dat = malloc(sizeof(*dat));
//	adm->dat = dat;
	adm.dat->x = 1;
	while (adm.dat->x)
	{
		adm.dat->arg = readline(prompt);
		add_history(adm.dat->arg);
		printf(GREEN"arg = [%s]"RESET"\n", adm.dat->arg);
		if (ft_strcmp(adm.dat->arg, "exit") == 0 || ft_chk_quote(&adm))
			adm.dat->x = 0;
		free(adm.dat->arg);
	}
	free(adm.dat);
	return (0);
}
