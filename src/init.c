/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:33:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/11 20:15:32 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void init_player_variables(t_cub *cub);
static void init_cub(t_cub *cub);

void init_struct(t_cub *cub)
{
	init_cub(cub);
	init_player_variables(cub);
}

static void init_player_variables(t_cub *cub)
{
	cub->player.pos_x = 0;
	cub->player.pos_y = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	cub->player.direction = '\0';
	cub->player.move_x = 0;
	cub->player.move_y = 0;
	cub->player.rotate = 0;
	cub->player.moved = 0;
}

static void init_cub(t_cub *cub)
{
	cub->map = NULL;
	cub->map_w = 0;
	cub->map_h = 0;
	cub->player_x = -1;
	cub->player_y = -1;
	cub->texture.no_path = NULL;
	cub->texture.so_path = NULL;
	cub->texture.we_path = NULL;
	cub->texture.ea_path = NULL;
	cub->texture.has_no = false;
	cub->texture.has_so = false;
	cub->texture.has_we = false;
	cub->texture.has_ea = false;
	cub->texture.has_floor = false;
	cub->texture.has_ceil = false;
	cub->texture.size = 0;
	cub->texture.index = 0;
	cub->texture.texture_x = 0;
	cub->texture.texture_y = 0;
	cub->pixels_text = NULL;
}
