/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:50:53 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 17:39:22 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int find_player(t_cub *cub)
{
	int i;
	int j;
	int player_count;

	player_count = 0;
	i = 0;
	while (i < cub->map.map_h)
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == 'N' || cub->map.map[i][j] == 'S' || cub->map.map[i][j] == 'E' || cub->map.map[i][j] == 'W')
			{
				set_player_position(cub, j, i, cub->map.map[i][j]);
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (error_msg("Map must have exactly one player."), 1);
	return (0);
}

static int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static void flood_fill(char **map_copy, int x, int y, int width, int height, int *invalid)
{
	if (y < 0 || y >= height || x < 0)
	{
		*invalid = 1;
		return;
	}
	if (x >= (int)ft_strlen(map_copy[y]))
	{
		*invalid = 1;
		return;
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'X')
		return;
	if (map_copy[y][x] == ' ')
	{
		*invalid = 1;
		return;
	}
	map_copy[y][x] = 'X';
	flood_fill(map_copy, x + 1, y, width, height, invalid);
	flood_fill(map_copy, x - 1, y, width, height, invalid);
	flood_fill(map_copy, x, y + 1, width, height, invalid);
	flood_fill(map_copy, x, y - 1, width, height, invalid);
}

int flood_fill_validation(t_cub *cub)
{
	char **map_copy;
	int i;
	int invalid = 0;

	map_copy = malloc(sizeof(char *) * cub->map.map_h);
	if (!map_copy)
		return (error_msg("Memory allocation failed."), 1);
	i = 0;
	while (i < cub->map.map_h)
	{
		map_copy[i] = ft_strdup(cub->map.map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (error_msg("Memory allocation failed."), 1);
		}
		i++;
	}
	flood_fill(map_copy, (int)cub->player.pos_x, (int)cub->player.pos_y,
			   cub->map.map_w, cub->map.map_h, &invalid);
	i = 0;
	while (i < cub->map.map_h)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	if (invalid)
		return (error_msg("Map is not properly enclosed by walls."), 1);
	return (0);
}

int validate_map_boundaries(t_cub *cub)
{
	int i, j;

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

int check_map_continuity(char **map_lines, int line_count)
{
	int i;
	int found_map = 0;
	int found_gap = 0;

	i = 0;
	while (i < line_count)
	{
		if (ft_is_map_line(map_lines[i]))
		{
			if (found_gap && found_map)
				return (error_msg("Map cannot be separated by empty lines."), 1);
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

int parse_map(const char *file, t_cub *cub)
{
	int fd;
	char **map_lines;
	int line_count;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Cannot open map file."), 1);
	if (read_map_lines(fd, &map_lines, &line_count))
		return (close(fd), error_msg("Failed to read map."), 1);
	close(fd);
	if (line_count == 0)
		return (error_msg("No map found."), 1);
	if (check_map_continuity(map_lines, line_count))
		return (1);
	calculate_map_dimensions(cub, map_lines, line_count);
	if (find_player(cub))
		return (1);
	if (validate_map_boundaries(cub))
		return (1);
	if (flood_fill_validation(cub))
		return (1);
	return (0);
}
