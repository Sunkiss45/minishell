/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:17:41 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/01 17:53:04 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	if (src)
	{
		while (src[j] != '\0')
		{
			dest[i + j] = src[j];
			j++;
		}
	}
	else
	{
		dest[i + j] = '\n';
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

static int	count(int size, char **strs)
{
	int	dest_size;
	int	sep_int;
	int	s;

	dest_size = 1;
	s = 0;
	while (s < size)
	{
		dest_size += ft_strlen(strs[s]);
		s++;
	}
	sep_int = 1;
	dest_size += sep_int * (size - 1);
	return (dest_size);
}

char	*ft_strjoin_n(int size, char **strs)
{
	char	*dest;
	int		i;

	if (size == 0)
	{
		dest = malloc(sizeof(char) * 1);
		if (dest == NULL)
			return (NULL);
		dest[0] = 0;
		return (dest);
	}
	dest = (char *)malloc(sizeof(char) * count(size, strs));
	if (dest == NULL)
		return (NULL);
	dest[0] = 0;
	i = 0;
	while (i < size)
	{
		dest = ft_strcat(dest, strs[i]);
		if (i < (size - 1))
			dest = ft_strcat(dest, NULL);
		i++;
	}
	return (dest);
}
