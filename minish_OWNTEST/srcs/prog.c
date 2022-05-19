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

// void	exec_builtin(t_adm *adm)
// {
// 	t_elm	*now;

// 	now = adm->head; 
// 	while (now != NULL)
// 	{
// 		if (now->t == 'b')
// 		{
// 			if (!ft_strncmp(now->str, "cd", 2) && now->next)
// 				ft_cd(adm, now->next);
// 			if (ft_strncmp(now->str,"echo", 4) == 0)
// 				ft_echo(now->next->str);
// 			if (ft_strcmp(now->str, "pwd") == 0)
// 				ft_pwd(); //OK
// 			if (ft_strncmp(now->str, "unset", 5) == 0)
// 				ft_unset(now->next->str, adm); //OK
// 			if (ft_strcmp(now->str, "env") == 0)
// 				ft_env(adm); //OK
// 			if (ft_strncmp(now->str, "export", 6) == 0)
// 				ft_export(&now->str[7], adm); //OK
// 			break ;
// 		}
// 		now = now->next;
// 	}
// 	exit (0);
// }

// void	exec_builtin(t_adm *adm, t_pip *pip)
// {
// //// definir dans pip->exec[1] les parametres des builtins ! ///////
// 	//if (!ft_strncmp(pip->exec[0], "cd", 2))
// //		ft_cd(adm, now->next);
// 	//if (ft_strncmp(pip->exec[0],"echo", 4) == 0)
// //		ft_echo(pip->exec[1]);
// //		ft_echo(now->next->str);
// 	if (ft_strcmp(pip->exec[0], "pwd") == 0)
// 		ft_pwd();
// 	//if (ft_strncmp(pip->exec[0], "unset", 5) == 0)
// //		ft_unset(now->next->str, adm);
// 	if (ft_strcmp(pip->exec[0], "env") == 0)
// 		ft_env(adm);
// 	//if (ft_strncmp(pip->exec[0], "export", 6) == 0)
// //		ft_export(&now->str[7], adm);
// }

int	exec_builtin(t_adm *adm, t_pip *pip)
{
	int	e;

	e = 0;
	if (!ft_strcmp(pip->exec[0], "echo"))
		e = ft_echo(pip);
	if (!ft_strcmp(pip->exec[0], "cd"))
		e = ft_cd(adm, pip);
	if (!ft_strcmp(pip->exec[0], "pwd"))
		e = ft_pwd();
	if (!ft_strcmp(pip->exec[0], "env"))
		e = ft_env(adm);
	if (!ft_strcmp(pip->exec[0], "unset"))
		e = ft_unset(pip->param, adm);
	if (!ft_strcmp(pip->exec[0], "export"))
		e = ft_export(pip->param, adm);
	exit (e);
}

void	close_all_fd(t_adm *adm)
{
	t_pip	*job;
	int		i;

	job = adm->piph;
	if (adm->p == 1)
	{
		i = -1;
		while (++i <= job->fd_count)
		{
			if (job->fd_count > 0 && i == job->fd_count)
				break ;
			close(job->fd_in[i]);
		}
		close(job->fd_out);
	}
	if (adm->p > 1)
	{
		while (job != NULL)
		{
			i = -1;
			while (++i < job->fd_count)
				if (job->fd_in[i] > 2)
					close(job->fd_in[i]);
			if (job->fd_count > 2)
				close(job->fd_out);
			job = job->next;
		}
	i = -1;
	while (++i < (adm->p * 2 - 2))
		close(adm->end[i]);
	}
}

int	open_pipes(t_adm *adm)
{
	int		i;

	i = 0;
	while (i < (adm->p * 2 - 2))
	{
		if (pipe(&adm->end[i]) == -1)
			return (ft_perror("open_pipes", -1));
		i += 2;
	}
	return (0);
}

void	wait_all_pid(t_adm *adm)
{
	int		j;
	t_pip	*job;

	j = 0;
	job = adm->piph;
	while (job != NULL && j < (adm->p + job->fd_count))
	{
		waitpid(adm->pid[j], NULL, 0);
		j++;
		job = job->next;
	}
}

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
			job->fd_in[0] = adm->end[((adm->p - 1) * 2) - 2];
		else
		{
			job->fd_in[0] = adm->end[j];
			job->fd_out = adm->end[j + 3];
			j += 2;
		}
		i++;
		job = job->next;
	}
}

void	ft_exec_job(t_adm *adm, t_pip *job, int j)
{
	int	i;

	i = -1;
	while (++i <= job->fd_count)
	{
		if (job->fd_count > 0 && i == job->fd_count)
			break ;
// ATTENTION ici il faut mute les signaux (pour eviter des pb)
		adm->pid[j] = fork();
		ft_signal(); // redefinir les signaux selon le comportement attendu
		if (adm->pid[j] < 0)
			return ;
		else if (adm->pid[j] == 0)
		{
			if (job->fd_count >= 0)
			{
				dup2(job->fd_in[i], STDIN_FILENO);
				dup2(job->fd_out, STDOUT_FILENO);
				close_all_fd(adm);
			}
			if (job->t == 'b')
				if (exec_builtin(adm, job) == -1)
					perror("exec_builtin");
			if (job->t == 'c')
				if (execve(job->exec[0], job->exec, adm->ev) == -1)
					perror("execve");
		}
	}
}

int	ft_execute_prog(t_adm *adm)
{
	t_pip	*job;
	int		j;

printf("ft_execute_prog\n");
	job = adm->piph;
// ATTENTION ici il faut mute les signaux (pour eviter des pb)
	if (adm->p == 1)
		ft_exec_job(adm, job, 0);
	else
	{
		if (open_pipes(adm) == -1)
			return (1);
		redir_pipe_ends(adm);
		j = -1;
		while (++j < adm->p)
		{
			ft_exec_job(adm, job, j);
			if (job->next)
				job = job->next;
		}
	}
	close_all_fd(adm);
	wait_all_pid(adm);
	ft_signal(); // ATTENTION ici remettre les signaux de base
	return (0);
}
