/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:33 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 18:28:25 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unsint(unsigned int num, int *total)
{
	if (num < 10)
		ft_putncount(num + 48, total);
	else
	{
		ft_unsint(num / 10, total);
		ft_putncount((num % 10) + 48, total);
	}
}
