/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:04:47 by rde-fari          #+#    #+#             */
/*   Updated: 2025/08/25 01:48:55 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	errorHandler(t_error error)
{
	const char	*messages[] = {
	[SUCCESS] = "",
	[INVALID_USAGE] = "Invalid program usage. Try './cub3D PATH_TO_MAP'"
	};

	if (error != SUCCESS)
		printf("%s", messages[error]);
}
