/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:37:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/10/20 17:11:08 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void clean_exit(t_cub *cub, int code)
{
	if (!cub)
		exit(code);
	if (cub->mlx.win_ptr && cub->mlx.mlx_ptr)
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	if (cub->mlx.mlx_ptr)
	{
		if (cub->mlx.img_ptr)
			mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img_ptr);
		mlx_destroy_display(cub->mlx.mlx_ptr);
		mlx_loop_end(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
	}
	free_structs(cub);
	exit(code);
}

int exit_cub3d(t_cub *cub)
{
	clean_exit(cub, 0);
	return (0);
}