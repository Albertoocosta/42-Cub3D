/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:16:57 by alberto           #+#    #+#             */
/*   Updated: 2025/10/23 15:56:49 by rde-fari         ###   ########.fr       */
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
		error_msg("Unable to load texture.");
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
		{
			error_msg("Malloc error.");
			clean_exit(cub, 1);
		}
		i++;
	}
}

void	load_textures(t_cub *cub)
{
	cub->texture.texture_grid = ft_calloc(4, sizeof(int *));
	if (!cub->texture.texture_grid)
	{
		error_msg("Malloc error.");
		clean_exit(cub, 1);
	}
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
	{
		error_msg("Malloc error.");
		clean_exit(cub, 1);
	}
	i = 0;
	while (i < HEIGHT)
	{
		cub->texture.pixels_text[i] = ft_calloc(WIDTH + 1,
				sizeof * cub->texture.pixels_text);
		if (!cub->texture.pixels_text[i])
		{
			error_msg("Malloc error.");
			clean_exit(cub, 1);
		}
		i++;
	}
}
