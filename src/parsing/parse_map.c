/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:00:00 by cda-fons          #+#    #+#             */
/*   Updated: 2025/10/14 16:56:39 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_player_position(t_cub *cub, int x, int y, char dir)
{
	cub->player.pos_x = (double)x + 0.5;
	cub->player.pos_y = (double)y + 0.5;
	cub->player.spawn_dir = dir;
	cub->map.map[y][x] = '0';
}

static char	**expand_map_array(char **map_lines, int line_count)
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

static int	add_map_line(char ***map_lines, int *line_count, char *line)
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

static void	calculate_map_dimensions(t_cub *cub, char **map_lines, int count)
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

static int	find_player(t_cub *cub)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (i < cub->map.map_h)
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == 'N' || cub->map.map[i][j] == 'S'
				|| cub->map.map[i][j] == 'E' || cub->map.map[i][j] == 'W')
			{
				set_player_position(cub, j, i, cub->map.map[i][j]);
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("Error\nMap must have exactly one player\n"), 1);
	return (0);
}

int	parse_map(const char *file, t_cub *cub)
{
	int		fd;
	char	**map_lines;
	int		line_count;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCannot open map file\n"), 1);
	if (read_map_lines(fd, &map_lines, &line_count))
		return (close(fd), printf("Error\nFailed to read map\n"), 1);
	close(fd);
	if (line_count == 0)
		return (printf("Error\nNo map found\n"), 1);
	calculate_map_dimensions(cub, map_lines, line_count);
	return (find_player(cub));
}
