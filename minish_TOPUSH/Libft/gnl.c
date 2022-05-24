/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:11:32 by ebarguil          #+#    #+#             */
/*   Updated: 2021/12/20 10:34:44 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

int	ft_strche(char *s, char c, int x)
{
	int	i;

	if (!s || (c != '\n' && c != '\0'))
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	if (c == '\0' || x)
		return (i);
	return (0);
}

char	*ft_join_gnl(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	s = malloc(sizeof(char) \
	* (ft_strche(s1, '\0', 0) + ft_strche(s2, '\0', 0) + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

char	*ft_cut(t_gnl *p, char *str)
{
	p->line = malloc(sizeof(char) * ft_strche(str, '\n', 1) + 1);
	if (p->line == NULL)
		return (ft_free(str));
	p->i = 0;
	while (str && str[p->i] && str[p->i] != '\n')
	{
		p->line[p->i] = str[p->i];
		p->i++;
	}
	p->line[p->i] = '\0';
	if (!str)
		return (NULL);
	p->i = ft_strche(str, '\n', 1);
	if (!str[p->i])
	{
		free(str);
		return (NULL);
	}
	p->i++;
	p->j = 0;
	while (str && str[p->i])
		str[p->j++] = str[p->i++];
	str[p->j] = '\0';
	return (str);
}

char	*gnl(int fd)
{
	static char	*str[1024];
	t_gnl		p;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, p.buf, 0) < 0)
		return (ft_free(str[fd]));
	p.r = 1;
	while (!ft_strche(str[fd], '\n', 0) && p.r != 0)
	{
		p.r = read(fd, p.buf, BUFFER_SIZE);
		if (p.r == -1)
			return (ft_free(str[fd]));
		p.buf[p.r] = '\0';
		p.tmp = str[fd];
		str[fd] = ft_join_gnl(p.tmp, p.buf);
		free(p.tmp);
		if (str[fd] == NULL)
			return (NULL);
	}
	str[fd] = ft_cut(&p, str[fd]);
	if (p.r == 0 && !str[fd] && !p.line[0])
		return (ft_free(p.line));
	return (p.line);
}
