/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:59:00 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/28 15:55:15 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_pipe_ends(t_adm *adm)
{
	t_pip	*job;
	int		i;
	int		j;

	job = adm->piph;
	i = 0;
	j = 0;
	while (job != NULL && i < adm->p)
	{
		if (i == 0)
			job->fd_out = adm->end[1];
		else if (i == adm->p - 1)
			job->fd_in = adm->end[((adm->p - 1) * 2) - 2];
		else
		{
			job->fd_in = adm->end[j];
			job->fd_out = adm->end[j + 3];
			j += 2;
		}
		i++;
		job = job->next;
	}
}

void	ft_exec_job(t_adm *adm, t_pip *job, int j)
{
	adm->pid[j] = fork();
	if (adm->pid[j] < 0)
		return ;
	else if (adm->pid[j] == 0)
	{
		if (job->t == '\0')
		{
			if (job->exec[0])
			{
				write(1, "minishell: ", 11);
				write(1, job->exec[0], ft_strlen(job->exec[0]));
				write(1, ": command not found\n", 20);
			}
			exec_builtin(adm, job, 1);
		}
		dup2(job->fd_in, STDIN_FILENO);
		dup2(job->fd_out, STDOUT_FILENO);
		if (job->t == 'b')
			if (exec_builtin(adm, job, 1) == -1)
				ft_perror("exec_builtin", -1);
		close_all_fd(adm);
		if (job->t == 'c')
			if (execve(job->exec[0], job->exec, adm->ev) == -1)
				ft_perror("execve", -1);
	}
}

int	ft_listev_to_tabev(t_adm *adm)
{
	t_env	*ev;
	char	*tmp;
	char	*ln;

	ev = adm->envh;
	ln = NULL;
	while (ev != NULL)
	{
		tmp = ln;
		ln = ft_strjoin_lib(tmp, ev->line);
		free(tmp);
		if (ln == NULL)
			return (1);
		tmp = ln;
		ln = ft_strjoin_lib(tmp, "\n");
		free(tmp);
		if (ln == NULL)
			return (1);
		ev = ev->next;
	}
	adm->ev = ft_split_lib(ln, '\n');
	free(ln);
	if (adm->ev == NULL)
		return (1);
	return (0);
}

int	ft_pipe_prog(t_adm *adm, t_pip *job)
{
	int	j;

	if (open_pipes(adm) == -1)
		return (1);
	redir_pipe_ends(adm);
	j = -1;
	while (job != NULL && ++j < adm->p)
	{
		ft_exec_job(adm, job, j);
		job = job->next;
	}
	close_all_fd(adm);
	return (0);
}

int	ft_execute_prog(t_adm *adm)
{
	t_pip	*job;
	char	*tmp[2];

	job = adm->piph;
	if (ft_listev_to_tabev(adm))
		return (ft_perror("list_to_tabev", -1));
	if (g_sig == 0)
		g_sig = 1;
	if (adm->p == 1 && job->t != 'b')
		ft_exec_job(adm, job, 0);
	else if (adm->p == 1 && job->t == 'b')
		if (exec_builtin(adm, job, 0) == -1)
			ft_perror(job->exec[0], -1);
	if (adm->p > 1)
		if (ft_pipe_prog(adm, job))
			return (1);
	close_all_fd(adm);
	tmp[0] = ft_itoa(wait_all_pid(adm));
	tmp[1] = ft_strjoin_lib("?=", tmp[0]);
	ft_export(tmp[1], adm);
	if (adm->ev)
		adm->ev = ft_free_split(adm->ev);
	g_sig = 0;
	return (free(tmp[0]), free(tmp[1]), 0);
}
