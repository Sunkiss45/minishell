/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:54:10 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/11 15:54:37 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///// A SUPR /////
void	print_pip(t_pip *pip)
{
	int	j;

	printf(RED"pip->t = [%c]"RESET"\n", pip->t);
	printf(RED"pip->pass = [%d]"RESET"\n", pip->pass);
	printf(RED"pip->fd_count = [%d]"RESET"\n", pip->fd_count);
	j = 0;
	if (pip->fd_count)
	{
		while (j < pip->fd_count)
		{
			printf(RED"pip->fd_in[%d] = [%d]"RESET"\n", j, pip->fd_in[j]);
			j++;
		}
	}
	else if (!pip->fd_count)
		printf(RED"pip->fd_in[%d] = [%d]"RESET"\n", j, pip->fd_in[j]);
	printf(RED"pip->fd_out = [%d]"RESET"\n", pip->fd_out);
	j = 0;
	while (pip->exec && pip->exec[j])
	{
		printf(RED"pip->exec[%d] = [%s]"RESET"\n", j, pip->exec[j]);
		j++;
	}
}
///// A SUPR /////

int ft_redir_out(t_adm *adm, t_pip *pip)
{
	t_elm	*now;
	int		i;

	now = adm->head;
	i = 0;
	while (now != NULL)
	{
		if (now->t == '>' && now->next && adm->i == adm->p - 1)
		{
			if (access(now->next->str, F_OK) != 0 || (access(now->next->str, R_OK | W_OK) != 0 && !unlink(now->next->str)))
				pip->fd_out = open(now->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				pip->fd_out = open(now->next->str, O_RDWR | O_TRUNC);
		}
		now = now->next;
	}
	return (-3);
}

int	readline_heredoc(char *delim)
{
	int		fd[2];
	char	*str;

	pipe(fd);
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (close(fd[1]), free(str),
				write(2, "heredoc warning : ended by end-of-file\n", 40), fd[0]);
		if (ft_strcmp(delim, str))
		{
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
			free(str);
		}
		else
			return (free(str), close(fd[1]), fd[0]);
	}
	return (-1);
}

int	ft_redir_in(t_adm *adm, t_pip *pip)
{
	t_elm	*now;
	int		i;

	now = adm->head;
	i = 0;
	while (now != NULL && now->t != '|')
	{
		pip->fd_in[i] = -2;
		if (now->t == 'f' && i < pip->fd_count)
		{
			pip->fd_in[i] = open(now->str, O_RDONLY);
			if (pip->fd_in[i] == -1)
				return (-1);
			i++;
		}
		if (now->t == 'w')
		{
			pip->fd_in[i] = readline_heredoc(now->str);
			if (pip->fd_in[i] == -1)
				return (-1);
		}
		now = now->next;
	}
	return (-3);
}
