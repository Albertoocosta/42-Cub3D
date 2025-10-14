/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:16:57 by alberto           #+#    #+#             */
/*   Updated: 2025/10/14 17:55:56 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	copy_texture_data(t_cub *cub, int index, int *data)
{
	int	i;

	i = 0;
	while (i < cub->texture.size * cub->texture.size)
	{
		cub->texture.texture_grid[index][i] = data[i];
		i++;
	}
}

void	load_texture_image(t_cub *cub, int index, char *path)
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;

	img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, path,
			&cub->texture.size, &cub->texture.size);
	if (!img)
	{
		printf("Error loading texture: %s\n", path);
		clean_exit(cub, 1);
	}
	data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	copy_texture_data(cub, index, data);
	mlx_destroy_image(cub->mlx.mlx_ptr, img);
}

static void	allocate_texture_grid(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->texture.texture_grid[i] = ft_calloc(cub->texture.size
				* cub->texture.size, sizeof(int));
		if (!cub->texture.texture_grid[i])
			clean_exit(cub, err_msg(NULL, "Malloc error", 1));
		i++;
	}
}

void	load_textures(t_cub *cub)
{
	cub->texture.texture_grid = ft_calloc(4, sizeof(int *));
	if (!cub->texture.texture_grid)
		clean_exit(cub, err_msg(NULL, "Malloc error", 1));
	allocate_texture_grid(cub);
	load_texture_image(cub, SO, cub->texture.no_path);
	load_texture_image(cub, NO, cub->texture.so_path);
	load_texture_image(cub, EA, cub->texture.we_path);
	load_texture_image(cub, WE, cub->texture.ea_path);
}

void	init_texture_pixel(t_cub *cub)
{
	int	i;

	if (cub->texture.pixels_text)
		free_tab_int(cub->texture.pixels_text, HEIGHT);
	cub->texture.pixels_text = ft_calloc(HEIGHT + 1,
			sizeof * cub->texture.pixels_text);
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