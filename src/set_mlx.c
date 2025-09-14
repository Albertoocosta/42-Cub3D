/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:34:50 by alberto           #+#    #+#             */
/*   Updated: 2025/09/14 17:42:53 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img(t_cub *cub, int width, int height)
{
	cub->mlx.img_ptr = mlx_new_image(cub->mlx.mlx_ptr, width, height);
	if (cub->mlx.img_ptr == NULL)
		printf("error init_img aloc\n"); //clean_exit(cub, message("mlx"));
	cub->mlx.img_addr = (int *)mlx_get_data_addr(cub->mlx.img_ptr,
		&cub->mlx.bits_per_pixel, &cub->mlx.size_line, &cub->mlx.endian);
	return ;
}

int	set_mlx(t_cub *cub)
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
