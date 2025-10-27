/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:34:50 by alberto           #+#    #+#             */
/*   Updated: 2025/10/23 16:00:55 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img(t_cub *cub, int width, int height)
{
	cub->mlx.img_ptr = mlx_new_image(cub->mlx.mlx_ptr, width, height);
	if (cub->mlx.img_ptr == NULL)
	{
		error_msg("Failed to create image.");
		clean_exit(cub, 1);
	}
	cub->mlx.img_addr = (int *)mlx_get_data_addr(cub->mlx.img_ptr,
			&cub->mlx.bits_per_pixel, &cub->mlx.size_line, &cub->mlx.endian);
}

static void	register_hooks(t_cub *cub)
{
	mlx_hook(cub->mlx.win_ptr, KeyPress, KeyPressMask,
		&key_press_handler, cub);
	mlx_hook(cub->mlx.win_ptr, KeyRelease, KeyReleaseMask,
		&key_release_handler, cub);
	mlx_hook(cub->mlx.win_ptr, DestroyNotify, StructureNotifyMask,
		&exit_cub3d, cub);
}

int	set_mlx(t_cub *cub)
{
	cub->mlx.mlx_ptr = mlx_init();
	if (cub->mlx.mlx_ptr == NULL)
		return (error_msg("Mlx error."), 1);
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr, WIDTH, HEIGHT,
			WIN_TITLE);
	if (cub->mlx.win_ptr == NULL)
		return (error_msg("Mlx error."), 1);
	cub->mlx.img_ptr = NULL;
	cub->mlx.img_addr = NULL;
	register_hooks(cub);
	return (0);
}
