/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:04:47 by rde-fari          #+#    #+#             */
/*   Updated: 2025/08/22 20:15:58 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


t_error	verify_arguments(int ac, char **av)
{
	if (ac != 1)
		return (INVALID_ARG_COUNT);
	(void)av;
	return (SUCCESS);
}

void	error_handler(t_error error)
{
	const char	*messages[] = {
	[SUCCESS] = "",
	[INVALID_ARG_COUNT] = "Invalid number of arguments!" 
	};

	if (error != SUCCESS)
		printf("%s", messages[error]);
}
