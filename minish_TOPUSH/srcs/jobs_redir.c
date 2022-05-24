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
/*void	print_pip(t_pip *pip)
{
	int	j;

	printf(BLUE"pip->t = [%c]"RESET"\n", pip->t);
	printf(BLUE"pip->param = [%s]"RESET"\n", pip->param);
	printf(BLUE"pip->fd_in = [%d]"RESET"\n", pip->fd_in);
	printf(BLUE"pip->fd_out = [%d]"RESET"\n", pip->fd_out);
	j = 0;
	while (pip->exec && pip->exec[j])
	{
		printf(BLUE"pip->exec[%d] = [%s]"RESET"\n", j, pip->exec[j]);
		j++;
	}
}*/
///// A SUPR /////

int	ft_append_fd(char *str)
{
	int	fd_out;

	if (access(str, F_OK) != 0
		|| (access(str, R_OK | W_OK) != 0 && !unlink(str)))
		fd_out = open(str, O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0644);
	else
		fd_out = open(str, O_APPEND | O_RDWR);
	return (fd_out);
}	

int	ft_open_fd(char *str)
{
	int	fd_out;

	if (access(str, F_OK) != 0
		|| (access(str, R_OK | W_OK) != 0 && !unlink(str)))
		fd_out = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd_out = open(str, O_RDWR | O_TRUNC);
	return (fd_out);
}

int	ft_redir_out(t_adm *adm, t_pip *pip)
{
	t_elm	*now;

	now = adm->head;
	while (now != NULL)
	{
		if ((now->t == '>' || now->t == 'a')
			&& now->next && adm->i == adm->p - 1)
		{
			if (now->t == '>')
				pip->fd_out = ft_open_fd(now->next->str);
			if (now->t == 'a')
				pip->fd_out = ft_append_fd(now->next->str);
		}
		now = now->next;
	}
	return (1);
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

	now = adm->head;
	if (adm->i != 0)
		return (0);
	while (now != NULL && !ft_strchr(now->t, ">a|"))
	{
		if (now->t == 'f' && now->prev && now->prev->t == '<')
		{
			if (pip->fd_in > 2)
				close(pip->fd_in);
			pip->fd_in = open(now->str, O_RDONLY);
			if (pip->fd_in == -1)
				return (-1);
		}
		if (now->t == 'w')
		{
			pip->fd_in = readline_heredoc(now->str);
			if (pip->fd_in == -1)
				return (-1);
			break ;
		}
		now = now->next;
	}
	return (0);
}
