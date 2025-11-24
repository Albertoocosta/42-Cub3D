/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   problem_solver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:06:51 by rde-fari          #+#    #+#             */
/*   Updated: 2025/11/24 15:35:07 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map(char *line)
{
	if (is_config_line(line)) {
		return (0);
	}
	else
	{
		if (!is_valid_map_char(*line) && *line != '\n')
			return (error_msg("Invalid map char found!"), 1);
	}
	return (0);
}

int	is_config_line(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (1);
	if (ft_strncmp(line, "F", 1) == 0)
		return (1);
	if (ft_strncmp(line, "C", 1) == 0)
		return (1);
	return (0);
}
