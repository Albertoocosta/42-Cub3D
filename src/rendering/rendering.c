/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:12:00 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 15:19:09 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_ray(t_ray *ray)
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

void set_frame(t_cub *cub, int x, int y)
{
	if (cub->pixels_text[y][x] > 0)
		set_image_pixel(cub, x, y, cub->pixels_text[y][x]);
	// else if(y < cub->map_h / 2)
	// 	set_image_pixel(cub, x, y, cub->texture.hex_ceiling);
	// else if (y < cub->map_h - 1)
	// 	set_image_pixel(cub, x, y, cub->texture.hex_floor);
}

void render_frame(t_cub *cub)
{
	int x;
	int y;

	// init_img(cub, cub->map_w, cub->map_h);
	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			set_frame(cub, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr,
							cub->mlx.img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img_ptr);
}

void rendering_ray(t_cub *cub)
{
	// init_texture(cub);
	init_ray(&cub->ray);
	raycasting(&cub->player, cub);
	render_frame(cub);
}

int rendering(t_cub *cub)
{
	cub->player.moved += move_player(cub);
	if (cub->player.moved == 0)
		return (0);
	rendering_ray(cub);
	return (0);
}