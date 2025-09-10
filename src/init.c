/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:33:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/10 12:49:32 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_game(t_game *game)
{
	init_config(&game->config);
	init_map(&game->map);
}

void	init_config(t_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;

	cfg->floor_rgb[0] = -1;
	cfg->floor_rgb[1] = -1;
	cfg->floor_rgb[2] = -1;
	cfg->ceil_rgb[0] = -1;
	cfg->ceil_rgb[1] = -1;
	cfg->ceil_rgb[2] = -1;

	cfg->has_no = false;
	cfg->has_so = false;
	cfg->has_we = false;
	cfg->has_ea = false;
	cfg->has_floor = false;
	cfg->has_ceil = false;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
}
