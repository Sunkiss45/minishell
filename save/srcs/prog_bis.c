/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:38:26 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/23 22:38:30 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(t_adm *adm)
{
	t_pip	*job;
	int		i;

	job = adm->piph;
	while (job != NULL)
	{
		if (job->fd_in > 2)
			close(job->fd_in);
		if (job->fd_out > 2)
			close(job->fd_out);
		job = job->next;
	}
	i = -1;
	while (++i < (adm->p * 2 - 2))
		close(adm->end[i]);
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

int	wait_all_pid(t_adm *adm)
{
	int		j;
	t_pip	*job;
	int		status;

	j = 0;
	job = adm->piph;
	status = 0;
	if (adm->p == 1 && job->t == 'b')
		return (status);
	while (job != NULL && j < (adm->p - 1))
	{
		waitpid(adm->pid[j], NULL, 0);
		j++;
		job = job->next;
	}
	waitpid(adm->pid[j], &status, WEXITSTATUS(status));
	return (status / 256);
}

int	exec_builtin_cmp(t_adm *adm, t_pip *pip)
{
	if (!ft_strcmp(pip->exec[0], "echo"))
		return (ft_echo(pip));
	if (!ft_strcmp(pip->exec[0], "cd"))
		return (ft_cd(adm, pip));
	if (!ft_strcmp(pip->exec[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(pip->exec[0], "env"))
		return (ft_env(adm, pip));
	if (!ft_strcmp(pip->exec[0], "unset") && pip->param)
		return (ft_unset(pip->param, adm));
	if (!ft_strcmp(pip->exec[0], "export"))
	{
		if (!pip->param)
			return (ft_export_alpha(adm));
		else
			return (ft_export(pip->param, adm));
	}
	return (0);
}

int	exec_builtin(t_adm *adm, t_pip *pip, int x)
{
	int	e;

	e = 0;
	e = exec_builtin_cmp(adm, pip);
	close_all_fd(adm);
	if (x == 0)
		return (e);
	ft_free_pip(adm);
	ft_free_list(adm);
	close(0);
	close(1);
	close(2);
	exit (ft_free(adm, NULL, e));
}
