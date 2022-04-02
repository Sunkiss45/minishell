/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:42:57 by ebarguil          #+#    #+#             */
/*   Updated: 2022/04/01 18:40:45 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_ope(char x, t_dat *data)
{
	if (data->c != 0)
	{
		data->ind[data->i] = data->c;
		if (data->c == x)
			data->c = 0;
	}
	else if (data->c == 0 && (x == '\'' || x == '\"'
			|| x == '<' || x == '>' || x == '|'))
	{
		data->ind[data->i] = x;
		if (x == '\'' || x == '\"')
			data->c = x;
	}
	else
		data->ind[data->i] = 0;
}

int	ft_parse_quote(char *arg, t_adm *adm, t_dat *dat)
{
	int	x;

	x = 0;
	dat->ind = malloc(sizeof(int) * ft_strlen(arg));
	if (dat->ind == NULL)
		return (1);
	dat->c = 0;
	dat->i = -1;
	while (arg[++dat->i])
		ft_parse_ope(arg[dat->i], dat);
	if (ft_init_list(arg, adm, dat))
	{
		ft_free_list(adm);
		x = 1;
	}
	free(dat->ind);
	return (x);
}

/*
	dat->i = -1;
	printf(GREEN"ind = [");
	while (arg[++dat->i])
		printf("%d", dat->ind[dat->i]);
	printf("]"RESET"\n");
*/

void	ft_pointer_pip(t_pip *pip, t_adm *adm)
{
	if (!adm->piph)
	{
		adm->piph = pip;
		adm->tail = pip;
		pip->next = NULL;
		pip->prev = NULL;
	}
	else
	{
		pip->prev = adm->pipt;
		adm->pipt->next = pip;
		pip->next = NULL;
		adm->pipt = pip;
	}
	pip->exec = NULL;
	pip->t = '\0';
	pip->pass = 0;
	pip->fd_count = 0;
	pip->fd_in[0] = 0;
	pip->fd_out = 1;
}

char	ft_found_type(t_elm *elm)
{
	char t;

	t = '\0';
	while (elm && elm->t != '|')
	{
		if (ft_strchr(elm->t, "cb"))
		{
			t = elm->t;
			break ;
		}
		elm = elm->next;
	}
	while (t && elm && elm->t != '|')
	{
		if (ft_strchr(elm->t, "cb"))
		{
			elm->t = '\0';
			is_file(elm);
		}
		elm = elm->next;
	}		
	return (t);
}

int	ft_count_op(t_elm *now)
{
	int	op;

	op = 0;
	while (now != NULL)
	{
		if (ft_strchr(now->t, "cbo"))
			op++;
		if (now->t == '|')
			break;
		now = now->next;
	}
	return (op);
}

char	**ft_create_exec(t_elm *now)
{
	char	**exec;
	int		op;
	int		i;

	op = ft_count_op(now);
	if (op != 0)
		exec = malloc(sizeof(char *) * (op + 1));
	i = -1;
	while (now != NULL && ++i != -1)
	{
		if (now->t == 'c')
			exec[i] = now->exe;
		if (now->t == 'b')
			exec[i] = now->str;
		if (now->t == 'o')
			exec[i] = now->str;
		if (now->t == '|')
			break;
		now = now->next;
	}
	if (op != 0)
		exec[i] = NULL;
	return (exec);
}

int	ft_open_file(t_adm *adm, int i)
{
	t_elm   *now;
	int		fd;
	
	now = adm->head;
	fd = -1;
	while (now != NULL)
	{
		if (now->t == 'f' && --i == 0)
		{
			fd = open(now->str, O_RDONLY);
printf(PURPLE"now->str = [%s], fd = %d"RESET"\n", now->str, fd);
			return (fd);
		}
		now = now->next;
	}
	return (fd);
}

int	ft_init_pip(t_adm *adm, t_elm *elm)
{
	t_pip	*pip;

	pip = malloc(sizeof(*pip));
	if (pip == NULL)
		return (1);
	ft_pointer_pip(pip, adm);
	pip->t = ft_found_type(elm);
	pip->exec = ft_create_exec(elm);
	return (0);
}

int	ft_parse_job(t_adm *adm, t_elm *elm)
{
	if (ft_init_pip(adm, elm))
		return (ft_perror("ft_init_pip", 1));
	
	return (0);
}

int	ft_job(char *arg, t_adm *adm)
{
	int		x;
	t_elm	*elm;

	if (ft_parse_quote(arg, adm, adm->dat))
		return (1);
	x = 0;
	elm = adm->head;
	while (elm != NULL)
	{
		printf(CYAN"[%s] = [%d]"RESET"\n", ft_strchr(elm->t, "cb<>"), x);
		if (!x && ft_strchr(elm->t, "cb<>"))
		{
			if (ft_parse_job(adm, elm))
				return (1);
			x = 1;
		}
		if (elm->t == '|')
			x = 0;
		elm = elm->next;
	}
	return (0);
}

int	ft_parse(t_adm *adm)
{
	int		i;
	int		q1;
	int		q2;
	char	*arg;

	i = -1;
	q1 = 0;
	q2 = 0;
	arg = adm->dat->arg;
	if (!arg || !arg[0])
		return (0);
	while (arg[++i])
	{
		if (arg[i] == '\'' && q2 % 2 == 0)
			q1++;
		if (arg[i] == '\"' && q1 % 2 == 0)
			q2++;
	}
	if (q1 % 2 == 0 && q2 % 2 == 0)
		return (ft_job(arg, adm));
	ft_putstr_fd("Quotes invalid !\n", 1);
	return (1);
}
