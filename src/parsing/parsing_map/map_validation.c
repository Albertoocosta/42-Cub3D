/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:50:53 by rde-fari          #+#    #+#             */
/*   Updated: 2025/11/24 15:38:44 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_player(t_cub *cub)
{
	int	i;
	int	j;
	int	player_count;

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
		return (error_msg("Map must have exactly one player."), 1);
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

static int	check_boundaries(t_cub *cub, char **map_copy, t_flood pos)
{
	if (pos.y < 0 || pos.y >= cub->map.map_h || pos.x < 0)
		return (1);
	if (pos.x >= (int)ft_strlen(map_copy[pos.y]))
		return (1);
	return (0);
}

void	flood_fill(t_cub *cub, char **map_copy, t_flood pos, int *invalid)
{
	if (check_boundaries(cub, map_copy, pos))
	{
		*invalid = 1;
		return ;
	}
	if (map_copy[pos.y][pos.x] == '1' || map_copy[pos.y][pos.x] == 'X')
		return ;
	if (map_copy[pos.y][pos.x] == ' ')
	{
		*invalid = 1;
		return ;
	}
	map_copy[pos.y][pos.x] = 'X';
	flood_fill(cub, map_copy, (t_flood){pos.x + 1, pos.y}, invalid);
	flood_fill(cub, map_copy, (t_flood){pos.x - 1, pos.y}, invalid);
	flood_fill(cub, map_copy, (t_flood){pos.x, pos.y + 1}, invalid);
	flood_fill(cub, map_copy, (t_flood){pos.x, pos.y - 1}, invalid);
}
