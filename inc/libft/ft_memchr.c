/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/10 12:42:09 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
	const char *src;
	size_t i;

	src = s;
	i = 0;
	while (i < n)
	{
		if (src[i] == (char)c)
			return ((char *)&src[i]);
		i++;
	}
	return (NULL);
}
