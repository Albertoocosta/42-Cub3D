/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:00:00 by cda-fons          #+#    #+#             */
/*   Updated: 2025/10/23 19:04:29 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player_position(t_cub *cub, int x, int y, char dir)
{
	cub->player.pos_x = (double)x + 0.5;
	cub->player.pos_y = (double)y + 0.5;
	cub->player.spawn_dir = dir;
	cub->map.map[y][x] = '0';
}

char	**expand_map_array(char **map_lines, int line_count)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (line_count + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		temp[i] = map_lines[i];
		i++;
	}
	temp[line_count + 1] = NULL;
	free(map_lines);
	return (temp);
}

int	add_map_line(char ***map_lines, int *line_count, char *line)
{
	char	**temp;

	temp = expand_map_array(*map_lines, *line_count);
	if (!temp)
		return (1);
	temp[*line_count] = ft_strdup(line);
	*map_lines = temp;
	(*line_count)++;
	return (0);
}

int	read_map_lines(int fd, char ***map_lines, int *line_count)
{
	char	*line;

	*map_lines = NULL;
	*line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_is_map_line(line)
			|| (*line_count > 0 && !ft_is_empty_line(line)))
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
