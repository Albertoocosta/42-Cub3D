/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:55:50 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/10 12:42:09 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_ptrhex(char format, unsigned long num, int *total)
{
	if (format == 'p' && num == 0)
	{
		ft_strncount("(nil)", total);
		return;
	}
	ft_strncount("0x", total);
	ft_hexapplier(format, num, total);
}
