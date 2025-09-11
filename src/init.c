/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:33:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/11 13:41:45 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player_variables(t_cub *cub)
{
	cub->player.pos_x = -1;
	cub->player.pos_y = -1;
	cub->player.dir_x = -1;
	cub->player.dir_y = -1;
	cub->player.plane_x = -1;
	cub->player.plane_y = -1;
	cub->player.direction = -1;
	cub->player.move_x = -1;
	cub->player.move_y = -1;
	cub->player.rotate = -1;
	cub->player.moved = -1;
}

static void init_cub(t_cub *cub)
{
	cub->map = NULL;
	cub->map_w = 0;
	cub->map_h = 0;
	cub->player_x = -1;
	cub->player_y = -1;
	cub->player_dir = '\0';
	cub->texture.north = NULL;
	cub->texture.south = NULL;
	cub->texture.west = NULL;
	cub->texture.east = NULL;
	cub->texture.floor = NULL;
	cub->texture.ceiling = NULL;
	cub->texture.hex_floor = 0;
	cub->texture.hex_ceiling = 0;
	cub->texture.size = 0;
	cub->texture.index = 0;
	cub->texture.step = 0;
	cub->texture.pos = 0;
	cub->texture.x = 0;
	cub->texture.y = 0;
	cub->texture_grid = NULL;
	cub->pixels_text = NULL;
}

void	init_struct(t_cub *cub)
{
	init_cub(cub);
	init_player_variables(cub);
}
