/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:12:00 by alberto           #+#    #+#             */
/*   Updated: 2025/09/14 17:37:06 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void set_frame(t_cub *cub, int x, int y)
{
	if (cub->texture.pixels_text[y][x] > 0)
		set_image_pixel(cub, x, y, cub->texture.pixels_text[y][x]);
	else if(y < cub->map.map_h / 2)
		set_image_pixel(cub, x, y, cub->texture.ceil_hex);
	else if (y < cub->map.map_h - 1)
		set_image_pixel(cub, x, y, cub->texture.floor_hex);
}

void render_frame(t_cub *cub)
{
	int x;
	int y;

	init_img(cub, WIDTH, HEIGHT);
	y = 0;
	while (y < cub->map.map_h)
	{
		x = 0;
		while (x < cub->map.map_w)
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
	init_texture_pixel(cub);
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
