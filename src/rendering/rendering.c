/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:12:00 by alberto           #+#    #+#             */
/*   Updated: 2025/10/21 18:14:25 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_frame(t_cub *cub, int x, int y)
{
	if (cub->texture.pixels_text[y][x] > 0)
		set_image_pixel(cub, x, y, cub->texture.pixels_text[y][x]);
	else if (y < HEIGHT / 2)
		set_image_pixel(cub, x, y, cub->texture.ceil_hex);
	else if (y < HEIGHT - 1)
		set_image_pixel(cub, x, y, cub->texture.floor_hex);
}

void	render_frame(t_cub *cub)
{
	int	x;
	int	y;

	init_img(cub, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_frame(cub, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr,
		cub->mlx.img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img_ptr);
	cub->mlx.img_ptr = NULL;
}

void	rendering_ray(t_cub *cub)
{
	init_texture_pixel(cub);
	raycasting(&cub->player, cub);
	render_frame(cub);
}

int	rendering(t_cub *cub)
{
	cub->player.moved += move_player(cub);
	if (cub->player.moved == 0)
		return (0);
	rendering_ray(cub);
	cub->player.moved = 0;
	return (0);
}
