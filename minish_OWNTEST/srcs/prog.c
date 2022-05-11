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
// }

// char	**ft_create_exec2(t_adm *adm)
// {
// 	char	**exec;
// 	t_elm	*now;
// 	int		op;
// 	int		i;

// 	op = 0;
// 	i = 0;
// 	now = adm->head; 
// 	while (now != NULL)
// 	{
// 		if (now->t == 'c' || now->t == 'o')
// 			op++;
// 		now = now->next;
// 	}
// 	if (op != 0)
// 		exec = malloc(sizeof(char *) * (op + 1));
// 	now = adm->head;
// 	while (now != NULL)
// 	{
// 		if (now->t == 'c')
// 		{
// 			exec[i] = now->exe;
// 			i++;
// 		}
// 		if (now->t == 'o')
// 		{
// 			exec[i] = now->str;
// 			i++;
// 		}
// 		now = now->next;
// 	}
// 	if (op != 0)
// 		exec[i] = NULL;
// 	return (exec);
// }

// int	ft_execute_prog(t_adm *adm)
// {
// 	int		i;
// 	int		pid[BUF_S];
// 	int		count_fd;
// 	int		fd_in;
// 	char	**exec;
// 	t_elm   *now;

// 	now = adm->head;
// 	fd_in = -1;
// //	exec_builtin(adm);
// 	if (adm->p == 1)
// 	{
// 		count_fd = 0;
// 		while (now != NULL)
// 		{
// 			if (now->t == 'f')
// 				count_fd++;
// 			now = now->next;
// 		}
// 		exec = ft_create_exec2(adm);
// 		i = -1;
// 		while (++i <= count_fd)
// 		{
// 			if (count_fd > 0 && i == count_fd)
// 				break ;
// //ATTENTION ici il faut mute les signaux (pour eviter des pb)
// 			pid[i] = fork();
// // redefinir les signaux selon le comportement attendu
// 			if (pid[i] < 0)
// 				return (1);
// 			else if (pid[i] == 0)
// 			{
// 				if (count_fd > 0)
// 				{
// 					//fd_in = ft_open_file(adm, i + 1);
// 					fd_in = ft_redir_fdin(adm, i + 1);
// 					dup2(fd_in, 0);
// 					close(fd_in);
// 				}
// 				if (execve(exec[0], exec, adm->ev) == -1)
// 					perror("execve");
// 			}
// 		}
// 		free(exec);
// 		i = -1;
// 		while (++i <= count_fd)
// 		{
// 			if (count_fd > 0 && i == count_fd)
// 				break ;
// 			waitpid(pid[i], NULL, 0);
// 		}
// //Remettre les signaux de base
// 	}
// 	return (0);
// }

//void	exec_builtin(t_pip *pip)
//{
//	t_elm	*now;

//	now = adm->head; 
//	while (now != NULL)
//	{
//		if (now->t == 'b')
//		{
					////// definir dans pip->exec[1] les parametres des builtins ! ///////
		//	if (!ft_strncmp(pip->exec[0], "cd", 2) && pip->next)
		//		ft_cd(adm, now->next);
	//		if (ft_strncmp(pip->exec[0],"echo", 4) == 0)
	//			ft_echo(pip->exec[1]);
	//			ft_echo(now->next->str);
		//	if (ft_strcmp(pip->exec[0], "pwd") == 0)
		//		ft_pwd();m
			// if (ft_strncmp(pip->exec[0], "unset", 5) == 0)
			// 	ft_unset(now->next->str, adm);
			// if (ft_strcmp(pip->exec[0], "env") == 0)
			// 	ft_env(adm);
			// if (ft_strncmp(pip->exec[0], "export", 6) == 0)
			// 	ft_export(&now->str[7], adm);
//			break ;
//		}
//		now = now->next;
//	}
//}

int	ft_execute_prog(t_adm *adm)
{
	t_pip	*job;
	int		pid[BUF_S];
	int		i;

printf("ft_execute_prog\n");
	job = adm->piph;
	if (adm->p == 1)
	{
		i = -1;
		while (++i <= job->fd_count)
		{
printf(CYAN"job->fd_count = [%d] | i = [%d]"RESET"\n", job->fd_count, i);
			if (job->fd_count > 0 && i == job->fd_count)
				break ;
// ATTENTION ici il faut mute les signaux (pour eviter des pb)
			pid[i] = fork();
// redefinir les signaux selon le comportement attendu
			if (pid[i] < 0)
				return (1);
			else if (pid[i] == 0)
			{
				// if (job->t == 'b')
				// {
				// 	exec_builtin(job);
				// }
				if (job->t == 'c')
				{
					if (job->fd_count >= 0)
					{
						dup2(job->fd_in[i], 0);
						dup2(job->fd_out, 1);
						close(job->fd_in[i]);
						close(job->fd_out);
					}
					if (execve(job->exec[0], job->exec, adm->ev) == -1)
						perror("execve");
				}
			}
		}
		i = -1;
		while (++i <= job->fd_count)
		{
			if (job->fd_count > 0 && i == job->fd_count)
				break ;
			waitpid(pid[i], NULL, 0);
		}
//Remettre les signaux de base
	}

	else if (adm->p != 1)
	{






	}

	return (0);
}
