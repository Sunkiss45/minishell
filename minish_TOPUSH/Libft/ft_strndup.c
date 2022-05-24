/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:48:35 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/16 11:52:59 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, int n)
{
	int		i;
	int		x;
	char	*dest;

	if (ft_strlen(src) < n)
		x = ft_strlen(src);
	else
		x = n;
	dest = malloc(sizeof(char) * x + 1);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (src[++i] && i < n)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
