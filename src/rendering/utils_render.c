/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:55:37 by alberto           #+#    #+#             */
/*   Updated: 2025/09/03 00:11:50 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	set_image_pixel(t_cub *cub, int x, int y, int color)
{
	int pixel;
	
	pixel = y * (cub->mlx.size_line / 4) + x;
	cub->mlx.img_addr[pixel] = color;
}

