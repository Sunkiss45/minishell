/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:27 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/24 16:44:49 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	else if (s1 && s2)
		while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
			i++;
	return (s1[i] - s2[i]);
}