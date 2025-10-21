/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:50:53 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/21 19:25:04 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
