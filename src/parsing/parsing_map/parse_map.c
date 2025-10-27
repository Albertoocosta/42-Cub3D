/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:00:00 by cda-fons          #+#    #+#             */
/*   Updated: 2025/10/24 19:04:50 by rde-fari         ###   ########.fr       */
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

void	free_map_lines(char **map_lines, int line_count)
{
	int	i;

	if (!map_lines)
		return ;
	i = 0;
	while (i < line_count)
	{
		if (map_lines[i])
			free(map_lines[i]);
		i++;
	}
	free(map_lines);
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

static char	*trim_newline(char *line)
{
	char	*trimmed;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, line, len);
	trimmed[len] = '\0';
	return (trimmed);
}

int	add_map_line(char ***map_lines, int *line_count, char *line)
{
	char		**temp;

	temp = expand_map_array(*map_lines, *line_count);
	if (!temp)
		return (1);
	temp[*line_count] = trim_newline(line);
	if (!temp[*line_count])
		return (1);
	*map_lines = temp;
	(*line_count)++;
	return (0);
}
