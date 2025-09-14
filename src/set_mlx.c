/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:34:50 by alberto           #+#    #+#             */
/*   Updated: 2025/09/14 19:09:41 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int set_mlx(t_cub *cub)
{
	cub->mlx.mlx_ptr = mlx_init();
	if (cub->mlx.mlx_ptr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr, WIDTH, HEIGHT,
									WIN_TITLE);
	if (cub->mlx.win_ptr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	cub->mlx.img_ptr = mlx_new_image(cub->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (cub->mlx.img_ptr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	cub->mlx.img_addr = (int *)mlx_get_data_addr(cub->mlx.img_ptr,
												&cub->mlx.bits_per_pixel, &cub->mlx.size_line, &cub->mlx.endian);
	if (cub->mlx.img_addr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	return (0);
}
