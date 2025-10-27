/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:03:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/27 16:45:53 by rde-fari         ###   ########.fr       */
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
			map_started = 1;
		if (map_started || ft_is_map_line(line))
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

int	validate_map_boundaries(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.map_h)
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (!is_valid_map_char(cub->map.map[i][j]))
				return (error_msg("Invalid character in map."), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_continuity(char **map_lines, int line_count)
{
	int	i;
	int	found_map;
	int	found_gap;

	found_gap = 0;
	found_map = 0;
	i = 0;
	while (i < line_count)
	{
		if (ft_is_map_line(map_lines[i]))
		{
			if (found_gap && found_map)
				return (error_msg("Map cannot be separated by empty line."), 1);
			found_map = 1;
		}
		else if (found_map && ft_is_empty_line(map_lines[i]))
		{
			found_gap = 1;
		}
		i++;
	}
	return (0);
}

int	parse_map(const char *file, t_cub *cub)
{
	int		fd;
	char	**map_lines;
	int		line_count;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Cannot open map file."), 1);
	if (read_map_lines(fd, &map_lines, &line_count))
		return (close(fd), error_msg("Failed to read map."), 1);
	close(fd);
	if (line_count == 0)
	{
		free_map_lines(map_lines, line_count);
		return (error_msg("No map found."), 1);
	}
	if (check_map_continuity(map_lines, line_count))
		return (free_map_lines(map_lines, line_count), 1);
	calculate_map_dimensions(cub, map_lines, line_count);
	if (find_player(cub))
		return (1);
	if (validate_map_boundaries(cub) || flood_fill_validation(cub))
		return (1);
	return (0);
}
