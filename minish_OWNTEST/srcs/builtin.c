/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:31:17 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/25 12:25:56 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_echo(char *s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i] != '\0')
// 	{
// 		if (write(1, &s[i], 1) == -1)
// 			ft_perror("echo", -1);
// 	}
// //	if (!option -n)
// 		write(1, "\n", 1);
// 	return (0);
// }

int	ft_echo(t_pip *pip)
{
	if (write(1, pip->param, ft_strlen(pip->param)) == -1)
		return (ft_perror("echo", -1));
	if (!(pip->exec[1] && !ft_strcmp(pip->exec[1], "-n")))
		if (write(1, "\n", 1) == -1)
			return (ft_perror("echo", -1));
	return (0);
}

// void	ft_cd(t_adm *adm, t_elm *elm)
// {
// 	char	*pathname;
// 	char	*buf;
// 	size_t	size;

// 	pathname = NULL;
// 	buf = NULL;
// 	size = 256;
// 	if (chdir(elm->str) != 0)
// 	{
// 		perror("cd");
// 		return ;
// 	}
// 	pathname = getcwd(buf, size);
// 	if (pathname == NULL)
// 	{
// 		perror("pwd");
// 		return ;
// 	}
// 	ft_unset("PWD", adm);
// 	ft_export(ft_strjoin_lib("PWD=", pathname), adm);
// 	return ;
// }

int	ft_cd(t_adm *adm, t_pip *pip)
{
	char	*pathname;
	char	*buf;
	size_t	size;

	pathname = NULL;
	buf = NULL;
	size = 256;
	if (chdir(pip->param) != 0)
		return (ft_perror("cd", -1));
	pathname = getcwd(buf, size);
	if (pathname == NULL)
		return (ft_perror("cd", -1), ft_return_free(pathname, -1));
	ft_unset("PWD", adm); //// ATTENTION
	ft_export(ft_strjoin_lib("PWD=", pathname), adm); //// ATTENTION
	return (ft_return_free(pathname, 0));
}

// void	ft_pwd(void)
// {
// 	char	*pathname;
// 	char	*buf;
// 	size_t	size;

// 	pathname = NULL;
// 	buf = NULL;
// 	size = 256;
// 	pathname = getcwd(buf, size);
// 	if (pathname == NULL)
// 		perror("pwd");
// 	else
// 	{
// 		ft_putstr_fd(pathname, 1);
// 		write(1, "\n", 1);
// 	}
// }

int	ft_pwd(void)
{
	char	*pathname;
	char	*buf;
	size_t	size;

	pathname = NULL;
	buf = NULL;
	size = 256;
	pathname = getcwd(buf, size);
	if (pathname == NULL)
		return (ft_perror("pwd", -1), ft_return_free(pathname, -1));
	if (write(1, pathname, ft_strlen(pathname)) == -1)
		return (ft_perror("pwd", -1), ft_return_free(pathname, -1));
	if (write(1, "\n", 1) == -1)
		return (ft_perror("pwd", -1));
	return (ft_return_free(pathname, 0));
}

// void	ft_export(char *s, t_adm *adm)
// {
// 	char	*tab_ev;
// 	int		s_ev;

// 	s_ev = 0;
// 	while (adm->ev[s_ev])
// 		s_ev++;
// 	tab_ev = ft_strjoin_n(s_ev, adm->ev);
// 	free(adm->ev);
// 	tab_ev = ft_strjoin_lib(tab_ev, "\n");
// 	tab_ev = ft_strjoin_lib(tab_ev, s);
// 	adm->ev = ft_split_lib(tab_ev, '\n');
// 	free(tab_ev);
// }

int	ft_export(char *s, t_adm *adm)
{
	char	*tab_ev;
	int		s_ev;

	s_ev = 0;
	while (adm->ev[s_ev])
		s_ev++;
	tab_ev = ft_strjoin_n(s_ev, adm->ev);
	free(adm->ev);
	tab_ev = ft_strjoin_lib(tab_ev, "\n");
	tab_ev = ft_strjoin_lib(tab_ev, s);
	adm->ev = ft_split_lib(tab_ev, '\n');
	free(tab_ev);
	return (0);
}

// void	ft_unset(char *s, t_adm *adm)
// {
// 	int	i;

// 	i = 0;
// 	while (adm->ev[i])
// 	{
// printf(YELLOW"ev[%d] = [%s]"RESET"\n", i, adm->ev[i]);
// 		if (strncmp(s, adm->ev[i], ft_strlen(s)) == 0)
// 			adm->ev[i] = NULL;
// printf(PURPLE"ev[%d] = [%s]"RESET"\n", i, adm->ev[i]);
// 		i++;
// 	}
// }

int	ft_unset(char *s, t_adm *adm)
{
	int		i;
	int		e;

	i = 0;
	e = -1;
	while (adm->ev[i])
	{
//printf(YELLOW"ev[%d] = [%s]"RESET"\n", i, adm->ev[i]);
		if (strncmp(s, adm->ev[i], ft_strlen(s)) == 0)
		{
			free(adm->ev[i]);
			adm->ev[i] = NULL;
printf(PURPLE"ev[%d] = [%s]"RESET"\n", i, adm->ev[i]);
			e = 0;
			return (e);
		}
		i++;
	}
	return (e);
}

// void	ft_env(t_adm *adm)
// {
// 	int	i;

// 	i = -1;
// 	while (adm->ev[++i])
// 	{
// 		ft_putstr_fd(adm->ev[i], 1);
// 		ft_putchar_fd('\n', 1);
// 	}
// }

int	ft_env(t_adm *adm)
{
	int	i;

	i = -1;
	while (adm->ev[++i])
	{
		if (write(1, adm->ev[i], ft_strlen(adm->ev[i])) == -1)
			return (ft_perror("env", -1));
		if (write(1, "\n", 1) == -1)
			return (ft_perror("env", -1));
	}
	return (0);
}
