/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:09:51 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/21 19:14:56 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_texture_index(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			cub->texture.index = WE;
		else
			cub->texture.index = EA;
	}
	else
	{
		if (ray->dir_y > 0)
			cub->texture.index = SO;
		else
			cub->texture.index = NO;
	}
}

static void	calculate_texture_params(t_texture *tex, t_ray *ray)
{
	tex->texture_x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->texture_x = tex->size - tex->texture_x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex->step;
}

static void	draw_textured_column(t_cub *cub, t_texture *tex, t_ray *ray, int x)
{
	int	y;
	int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->texture_y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = cub->texture.texture_grid[tex->index][tex->size
			* tex->texture_y + tex->texture_x];
		if (tex->index == NO || tex->index == EA)
			color = (color >> 1) & 8355711;
		if (color > 0)
			cub->texture.pixels_text[y][x] = color;
		y++;
	}
}

void	update_pixel(t_cub *cub, t_texture *tex, t_ray *ray, int x)
{
	get_texture_index(cub, ray);
	calculate_texture_params(tex, ray);
	draw_textured_column(cub, tex, ray, x);
}
