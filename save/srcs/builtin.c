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

int	ft_echo(t_pip *pip)
{
	write(pip->fd_out, pip->param, ft_strlen(pip->param));
	if (!(pip->exec[1] && !ft_strcmp(pip->exec[1], "-n")))
		write(pip->fd_out, "\n", 1);
	return (0);
}

int	ft_cd(t_adm *adm, t_pip *pip)
{
	char	*tmp[2];

	tmp[0] = NULL;
	tmp[0] = getcwd(NULL, 256);
	if (tmp[0] == NULL)
		return (-1);
	tmp[1] = ft_strjoin_lib("OLDPWD=", tmp[0]);
	ft_export(tmp[1], adm);
	free(tmp[1]);
	free(tmp[0]);
	if (!pip->param)
	{
		errno = 2;
		return (-1);
	}
	if (chdir(pip->param) != 0)
		return (-1);
	tmp[0] = NULL;
	tmp[0] = getcwd(NULL, 256);
	if (tmp[0] == NULL)
		return (-1);
	tmp[1] = ft_strjoin_lib("PWD=", tmp[0]);
	ft_export(tmp[1], adm);
	free(tmp[1]);
	return (ft_return_free(tmp[0], 0));
}

int	ft_pwd(void)
{
	char	*pathname;

	pathname = NULL;
	pathname = getcwd(NULL, 256);
	if (pathname == NULL)
		return (ft_return_free(pathname, -1));
	if (write(1, pathname, ft_strlen(pathname)) == -1)
		return (ft_return_free(pathname, -1));
	write(1, "\n", 1);
	return (ft_return_free(pathname, 0));
}

int	ft_unset(char *s, t_adm *adm)
{
	t_env	*ev;
	int		i;
	char	**vars;

	vars = ft_split_lib(s, ' ');
	if (vars == NULL)
		return (-1);
	i = -1;
	while (vars && vars[++i])
	{
		ev = adm->envh;
		while (ev != NULL)
		{
			if (!strcmp(vars[i], ev->var))
			{
				ft_supr_ev(adm, ev);
				break ;
			}
			ev = ev->next;
		}
	}
	return (ft_free_split(vars), 0);
}

int	ft_env(t_adm *adm, t_pip *pip)
{
	t_env	*ev;

	ev = adm->envh;
	while (ev != NULL)
	{
		write(pip->fd_out, ev->line, ft_strlen(ev->line));
		write(pip->fd_out, "\n", 1);
		ev = ev->next;
	}
	return (0);
}
