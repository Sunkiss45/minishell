/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:02:17 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/25 22:02:42 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getrows(char const *s, char c)
{
	size_t	rows;
	size_t	i;

	rows = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			rows++;
		i++;
	}
	return (rows);
}

static size_t	ft_wordlen(char const *s2, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s2[i] != c && s2[i])
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_free(char const **tab, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free((void *)tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static char	**ft_filltab(char const *s, size_t rows, char c, char **tab)
{
	size_t	t[3];

	t[0] = 0;
	t[1] = 0;
	rows = ft_getrows(s, c);
	while (s[t[0]] && t[1] < rows)
	{
		t[2] = 0;
		while (s[t[0]] == c)
			t[0]++;
		tab[t[1]] = (char *)malloc(sizeof(char) * ft_wordlen(s, c, t[0]) + 1);
		if (tab[t[1]] == NULL)
			return (ft_free((char const **)tab, rows));
		while (s[t[0]] && s[t[0]] != c)
		{
			tab[t[1]][t[2]] = s[t[0]];
			t[2]++;
			t[0]++;
		}
		tab[t[1]][t[2]] = '\0';
		t[1]++;
	}
	tab[t[1]] = 0;
	return (tab);
}

char	**ft_split_lib(char *s, char c)
{
	char	**tab;
	size_t	rows;

	if (!s)
		return (0);
	rows = ft_getrows(s, c);
	tab = (char **)malloc(sizeof(char *) * (rows + 1));
	if (tab == NULL)
		return (NULL);
	return (ft_filltab(s, rows, c, tab));
}
