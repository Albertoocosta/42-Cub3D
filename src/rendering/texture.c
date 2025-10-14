/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:16:57 by alberto           #+#    #+#             */
/*   Updated: 2025/10/01 02:02:07 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texture_pixel(t_cub *cub)
{
	int	i;

	if (cub->texture.pixels_text)
		free_tab_int(cub->texture.pixels_text, HEIGHT);
	cub->texture.pixels_text = ft_calloc(HEIGHT + 1, sizeof * cub->texture.pixels_text);
	if (!cub->texture.pixels_text)
		clean_exit(cub, err_msg(NULL, "Malloc error", 1));
	i = 0;
	while (i < HEIGHT)
	{
		cub->texture.pixels_text[i] = ft_calloc(WIDTH + 1, 
			sizeof * cub->texture.pixels_text);
		if (!cub->texture.pixels_text[i])
			clean_exit(cub, err_msg(NULL, "Malloc error", 1));
		i++;
	}
}

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

void	update_pixel(t_cub *cub, t_texture *tex, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(cub, ray);
	tex->texture_x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->texture_x = tex->size - tex->texture_x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex->step;
	y = ray->draw_start;
	while(y < ray->draw_end)
	{
		tex->texture_y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = cub->texture.texture_grid[tex->index][tex->size * tex->texture_y + tex->texture_x];
		if (tex->index == NO || tex->index == EA)
			color = (color >> 1) & 8355711;
		if (color > 0)
			cub->texture.pixels_text[y][x] = color;
		y++;
	}
}