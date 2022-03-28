/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:59:00 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/25 16:17:21 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // void	exec_builtin(t_adm *adm)
// // {
// // 	t_elm	*now;

// // 	now = adm->head; 
// // 	while (now != NULL)
// // 	{
// // 		if (now->t == 'b')
// // 		{
// // 			if (ft_strncmp(now->str, "cd", 2) == 0)
// // 				ft_cd(adm);
// // 			if (ft_strncmp(now->str,"echo", 4) == 0)
// // 				ft_echo(now->next->str);
// // 			if (ft_strcmp(now->str, "pwd") == 0)
// // 				ft_pwd(); //OK
// // 			if (ft_strncmp(now->str, "unset", 5) == 0)
// // 				ft_unset(now->next->str, adm); //OK
// // 			if (ft_strcmp(now->str, "env") == 0)
// // 				ft_env(adm); //OK
// // 			if (ft_strncmp(now->str, "export", 6) == 0)
// // 				ft_export(&now->str[7], adm); //OK
// // 			break ;
// // 		}
// // 		now = now->next;
// // 	}
// // }

// char	**ft_create_exec(t_adm *adm)
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

// int	ft_open_file(t_adm *adm, int i)
// {
// 	t_elm   *now;
// 	int		fd;
	
// 	now = adm->head;
// 	fd = -1;
// 	while (now != NULL)
// 	{
// 		if (now->t == 'f' && --i == 0)
// 		{
// 			fd = open(now->str, O_RDONLY);
// 			return (fd);
// 		}
// 		now = now->next;
// 	}
// 	return (fd);
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
// 	if (adm->p == 1)
// 	{
// 		count_fd = 0;
// 		while (now != NULL)
// 		{
// 			if (now->t == 'f')
// 				count_fd++;
// 			now = now->next;
// 		}
// 		exec = ft_create_exec(adm);
// 		i = -1;
// 		while (++i <= count_fd)
// 		{
// 			if (count_fd > 0 && i == count_fd)
// 				break ;
// 			pid[i] = fork();
// 			if (pid[i] < 0)
// 				return (1);
// 			else if (pid[i] == 0)
// 			{
// 				if (count_fd > 0)
// 				{
// 					fd_in = ft_open_file(adm, i + 1);
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
// 	}
// 	return (0);
// }

int	ft_execute_prog(t_adm *adm)
{
	

	return (0);
}
