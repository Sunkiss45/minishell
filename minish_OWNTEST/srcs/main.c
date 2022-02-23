/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:37:03 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/23 17:54:20 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_quote(char *arg, t_quo *data)
{
	if (data->oc && arg[data->i] == data->c)
	{
		data->ind[data->i] = 1;
		data->oc = 0;
		data->c = 0;
	}
	else if (data->oc)
		data->ind[data->i] = 1;
	else if (!data->oc && (arg[data->i] == '\'' || arg[data->i] == '\"'))
	{
		data->ind[data->i] = 1;
		data->oc = 1;
		data->c = arg[data->i];
	}
	else
		data->ind[data->i] = 0;
}

int	ft_cut_quote(char *arg, t_lst *lst)
{
	t_quo	data;

	lst = NULL;

	data.ind = malloc(sizeof(int) * ft_strlen(arg));
	if (!data.ind)
		return (1);
	data.oc = 0;
	data.c = 0;
	data.i = -1;
	while (arg[++data.i])
		ft_parse_quote(arg, &data);
	data.i = -1;
	printf(GREEN"ind = [");
	while (arg[++data.i])
		printf("%d", data.ind[data.i]);
	printf("]"RESET"\n");
// fct decouper la ligne par 0 et 1 en malloc
// fct decouper chaque ligne par ' ' (hors 1)
	free(data.ind);
	return (0);
}

int	ft_chk_quote(char *arg, t_lst *lst)
{
	int	i;
	int	q1;
	int	q2;

	i = -1;
	q1 = 0;
	q2 = 0;
	if (!arg[0])
		return (1);
	while (arg[++i])
	{
		if (arg[i] == '\'' && q2 % 2 == 0)
			q1++;
		if (arg[i] == '\"' && q1 % 2 == 0)
			q2++;
	}
//	printf(GREEN"q1 \' = [%d] | q2 \" = [%d]"RESET"\n", q1, q2);
	if (q1 % 2 == 0 && q2 % 2 == 0)
		return (ft_cut_quote(arg, lst));
	printf(CYAN"please verify your quotes !"RESET"\n");
	return (1);
}

int	main(int ac, char **av, char **ev)
{
	char	*arg;
	char	*prompt;
	t_lst	lst;
	int		x;

	av = NULL;
	ev = NULL;
	prompt = "minishell $> ";
	if (ac != 1)
	{
		errno = 2;
		perror("minishell");
		return (0);
	}
	x = 1;
	while (x)
	{
		arg = readline(prompt);
		add_history(arg);
		printf(GREEN"arg = [%s]"RESET"\n", arg);
		if (ft_chk_quote(arg, &lst))
			printf(RED"ya un blem"RESET"\n");
		if (arg[0] == 'e' && arg[1] == 'x' && arg[2] == 'i' && arg[3] == 't')
			x = 0;
		free(arg);
	}
	return (0);
}
