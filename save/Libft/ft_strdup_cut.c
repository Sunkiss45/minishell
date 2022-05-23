/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_cut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:02:59 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/03 15:28:09 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_cut(char *str, char c)
{
	char	*s;
	int		i;
	int		j;
	int		n;

	i = -1;
	n = 0;
	while (str && str[++i])
		if (str[i] == c)
			n++;
	s = malloc(sizeof(char) * ((ft_strlen(str) - n) + 1));
	if (s == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (str && str[++i])
		if (str[i] != c)
			s[++j] = str[i];
	s[++j] = '\0';
	return (s);
}
