/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:03:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 19:06:05 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	read_map_lines(int fd, char ***map_lines, int *line_count)
{
	char	*line;
	int		map_started;

	map_started = 0;
	*map_lines = NULL;
	*line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_is_map_line(line))
		{
			map_started = 1;
			if (add_map_line(map_lines, line_count, line))
				return (free(line), 1);
		}
		else if (map_started && !ft_is_empty_line(line))
		{
			if (add_map_line(map_lines, line_count, line))
				return (free(line), 1);
		}
		else if (map_started && ft_is_empty_line(line))
		{
			if (add_map_line(map_lines, line_count, line))
				return (free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

void	calculate_map_dimensions(t_cub *cub, char **map_lines, int count)
{
	int	i;

	cub->map.map = map_lines;
	cub->map.map_h = count;
	cub->map.map_w = 0;
	i = 0;
	while (i < count)
	{
		if ((int)ft_strlen(map_lines[i]) > cub->map.map_w)
			cub->map.map_w = ft_strlen(map_lines[i]);
		i++;
	}
}
