/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:33 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/16 16:44:24 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if ((!s1 && s2) || (s1 && !s2))
		return (1);
	if ((s1[0] == '\0' && s2[0] != '\0') || (s1[0] != '\0' && s2[0] == '\0'))
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
