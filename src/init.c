/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:33:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/12 19:22:44 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void init_player_variables(t_player *player);
static void init_texture(t_texture *texture);
static void init_map(t_map *map);

void init_cub(t_cub *cub)
{
	init_map(&cub->map);
	init_player_variables(&cub->player);
	init_texture(&cub->texture);
}

static void init_player_variables(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->spawn_dir = '\0';
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	player->moved = 0;
}

static void init_texture(t_texture *texture)
{
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->has_no = false;
	texture->has_so = false;
	texture->has_we = false;
	texture->has_ea = false;
	texture->has_floor = false;
	texture->has_ceil = false;
	texture->size = 0;
	texture->index = 0;
	texture->texture_x = 0;
	texture->texture_y = 0;
}

static void init_map(t_map *map)
{
	map->map = NULL;
	map->map_w = 0;
	map->map_h = 0;
}
