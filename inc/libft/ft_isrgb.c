/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isrgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:19:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/14 18:16:03 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int nbr_of_blocks(const char *str);

bool ft_isrgb(const char *str)
{
	printf("NOB = %d\nSTR = %s\n", nbr_of_blocks(str), str);
	if (nbr_of_blocks(str) == 3)
		return (true);
	return (false);
}

static int nbr_of_blocks(const char *str)
{
	int blocks = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\0')
			break;
		while (str[i] && (str[i] == ' ' || str[i] == ','))
			i++;
		if (str[i] == '\n' && str[i + 1] == '\0')
			break;
		if (ft_isdigit(str[i]))
		{
			blocks++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
		else if (str[i])
			return (0);
	}
	if (str[i] == '\n' && str[i + 1] == '\0')
		return (blocks);
	if (str[i] == '\0')
		return (blocks);
	return (0);
}
// 255, 255, 255 valido
// 255, 255, 25 5 invalido
// 255, 255, 25a5 invalido
// 255,255,255 valido