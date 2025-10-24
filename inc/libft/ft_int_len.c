/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:01:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 18:11:33 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_len(int num)
{
	int	value;

	if (num == 0)
		return (1);
	value = 0;
	if (num < 0)
	{
		value += 1;
		num *= (-1);
	}
	while (num != 0)
	{
		num = num / 10;
		value++;
	}
	return (value);
}
