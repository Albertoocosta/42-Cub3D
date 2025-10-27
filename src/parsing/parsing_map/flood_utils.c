/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:40:34 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/27 16:40:56 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**copy_map(t_cub *cub, int *error)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * cub->map.map_h);
	if (!map_copy)
		return (*error = 1, NULL);
	i = 0;
	while (i < cub->map.map_h)
	{
		map_copy[i] = ft_strdup(cub->map.map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (*error = 1, NULL);
		}
		i++;
	}
	return (map_copy);
}

static void	free_map_copy(char **map_copy, int map_h)
{
	int	i;

	i = 0;
	while (i < map_h)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

int	flood_fill_validation(t_cub *cub)
{
	char	**map_copy;
	int		invalid;
	int		error;

	invalid = 0;
	error = 0;
	map_copy = copy_map(cub, &error);
	if (error)
		return (error_msg("Memory allocation failed."), 1);
	if (!map_copy)
		return (1);
	flood_fill(cub, map_copy, (t_flood){(int)cub->player.pos_x,
		(int)cub->player.pos_y}, &invalid);
	free_map_copy(map_copy, cub->map.map_h);
	if (invalid)
		return (error_msg("Map is not properly enclosed by walls."), 1);
	return (0);
}
