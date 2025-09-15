/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:37:04 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/15 18:57:14 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int parse_file(int fd)
{
	char *line;
	bool map_started = false;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (ft_is_map_line(line))
			map_started = true;
		if (map_started)
		{
			free(line);
			return (printf("Error!\nMap must be the last element.\n"), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
