/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intncount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:01:08 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 18:11:45 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_intncount(va_list ap, char format, int *total)
{
	int	i;

	i = va_arg(ap, int);
	if (format == 'd' || format == 'i')
	{
		ft_putnbr_fd(i, 1);
		*total += ft_int_len(i);
	}
	else
	{
		ft_unsint(i, total);
	}
}
