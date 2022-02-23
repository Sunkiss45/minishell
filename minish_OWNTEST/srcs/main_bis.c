/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:31:27 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/22 14:42:14 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/*char	**ft_splitting(arg)
{
	return (split);
}*/

int	main(int ac, char **av, char **ev)
{
	char	*arg;
	char	*prompt;
	int		i;
	int		quot1;
	int		quot2;
	t_pip	p;
//	char	**split;

	av = NULL;
	prompt = "minishell $> ";
	if (ac != 1)
	{
		errno = 2;
		perror("minishell");
		return (0);
	}
	p.i = -1;
	while (ev[++p.i])
		if (ev[p.i][0] == 'P' && ev[p.i][1] == 'A' && ev[p.i][2] == 'T'
			&& ev[p.i][3] == 'H' && ev[p.i][4] == '=')
			p.pth = ft_split_add(&ev[p.i][5], ':');
	if (p.pth == NULL)
		return (1);
	while (1)
	{
		i = 0;
		quot1 = 0;
		quot2 = 0;
		arg = readline(prompt);
		add_history(arg);
		printf(RED"arg = [%s] | i = %d"RESET"\n", arg, i);
		while (arg[i])
		{
//			printf(YELLOW"[%c]"RESET"\n", arg[i]);
			if (arg[i] == '\'' && quot2 % 2 == 0)
				quot1++;
			if (arg[i] == '\"' && quot1 % 2 == 0)
				quot2++;
			i++;
		}
		printf(GREEN"quot1 = [%d] | quot2 = [%d]"RESET"\n", quot1, quot2);
		if (quot1 % 2 != 0 || quot2 % 2 != 0)
			printf(CYAN"please verify your quotes !"RESET"\n");
/*		spl = ft_split(arg, ' ');
		i = -1;
		while (spl[++i])
			printf(YELLOW"spl[%d] = [%s]"RESET"\n", i, spl[i]);*/
	}
	return (0);
}
