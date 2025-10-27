/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:33:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/23 18:18:54 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player_variables(t_player *player);
static void	init_texture(t_texture *texture);
static void	init_map(t_map *map);

void	init_cub(t_cub *cub)
{
	cub->mlx.mlx_ptr = NULL;
	init_player_variables(&cub->player);
	init_texture(&cub->texture);
	init_map(&cub->map);
}

static void	init_player_variables(t_player *player)
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

static void	init_texture(t_texture *texture)
{
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->floor_hex = 0;
	texture->ceil_hex = 0;
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
	texture->pixels_text = NULL;
	texture->texture_grid = NULL;
}

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_w = 0;
	map->map_h = 0;
}

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}
