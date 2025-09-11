/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:33:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/11 13:13:18 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_cub(t_cub *cub)
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
	// Inicialize player e ray conforme necessário
	cub->player.pos_x = 0;
	cub->player.pos_y = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	cub->player.direction = 0;
	cub->player.move_x = 0;
	cub->player.move_y = 0;
	cub->player.rotate = 0;
	cub->player.moved = 0;
	// zere ray
	cub->ray.camera_x = 0;
	cub->ray.dir_x = 0;
	cub->ray.dir_y = 0;
	cub->ray.map_x = 0;
	cub->ray.map_y = 0;
	cub->ray.step_x = 0;
	cub->ray.step_y = 0;
	cub->ray.sidedist_x = 0;
	cub->ray.sidedist_y = 0;
	cub->ray.deltadist_x = 0;
	cub->ray.deltadist_y = 0;
	cub->ray.wall_dist = 0;
	cub->ray.wall_x = 0;
	cub->ray.side = 0;
	cub->ray.line_height = 0;
	cub->ray.draw_start = 0;
	cub->ray.draw_end = 0;
}
