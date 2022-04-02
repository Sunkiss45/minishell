/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <ebarguil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:00:01 by ebarguil          #+#    #+#             */
/*   Updated: 2022/03/31 17:12:38 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strchr(char c, char *set)
{
	int	i;

	i = -1;
	while (set && set[++i])
		if (set[i] == c)
			return (&set[i]);
	return (NULL);
}