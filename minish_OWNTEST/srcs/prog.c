/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:59:00 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/21 15:45:25 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
// //printf(PURPLE"nb de lignes d'exec = [%d]"RESET"\n", op);
// 	if (op != 0)
// 		exec = malloc(sizeof(char *) * op);
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
// 	return (exec);
// }

// int	ft_execute_prog(t_adm *adm)//main(t_pip *pipcell, t_copy *cmdargs, int fdd)
// {
// 	int		end[2];
// 	int		pid;
// //	int		fd_entree;
// 	char	**exec;
// 	t_elm   *now;
// //	int		tty;
// //	char	*msh;

// 	now = adm->head;
// 	adm->rd_in = 0;
// //	adm->rd_out = 1;
// //	adm->rd_err = 2;
// //	fd_entree = -1;
// 	while (now != NULL)
// 	{
// 		if (now->t == 'f')
// 		{
// 			adm->fd = open(now->str, O_RDONLY);
// //			fd_entree = open(now->str, O_RDONLY);
// printf(PURPLE"now->str = [%s], fd_entree = %d"RESET"\n", now->str, adm->fd);//fd_entree);
// 			break ;
// 		}
// 		now = now->next;
// 	}
// //printf(RED"fd_entree = %d"RESET"\n", adm->fd);//fd_entree);
// //	msh = ttyname(fd_entree);
// //	tty = isatty(fd_entree);
// //printf(YELLOW"ttyname = [%s] | tty = %d"RESET"\n", msh, tty);
// 	end[0] = -1;
// 	end[1] = -1;
// 	if (pipe(end) == -1)
// 		return (1);
// 	if (adm->p == 0)
// 	{	
// 		exec = ft_create_exec(adm);
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			close(end[0]);
// 			close(end[1]);
// 			close(adm->fd);
// //			close(fd_entree);
// 			return (1);
// 		}
// 		else if (pid == 0)
// 		{
// 			close(end[0]);
// //			close(0);
// 			dup2(adm->fd, 0); // voir si utiliser dup2 ?
// 			close(adm->fd);
// //			dup2(fd_entree, 0); // voir si utiliser dup2 ?
// //			close(fd_entree);
// //			ft_child(adm, end, &fd_entree);
// //			execution(cmdargs, 1);
// //			msh = ttyname(0);
// //			tty = isatty(0);
// //printf(RED"ttyname = [%s] | tty = %d"RESET"\n", msh, tty);
// printf(CYAN"exec[0]= [%s] | exec[1] = [%s]"RESET"\n", exec[0], exec[1]);
// 			if (execve(exec[0], exec, adm->ev) == -1)
// 				perror("execve");
// //			ft_exit(cmdargs, 0);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			close(end[1]);
// 			adm->fd = end[0];
// //			fd_entree = end[0];
// 		}
// 	}
	
// //	status_child();
// //	close(fd_entree);
// //	close(end[1]);
// 	else
// 		pid = 0;
// //printf(BLUE"On arrive la ?"RESET"\n");

// 	adm->rd_in = -1;
// 	return (0);
// //	return (end[0]);
// }

int	ft_execute_prog(t_adm *adm)
{
    t_elm   *elm;

    elm = adm->head;
	return (0);
}
