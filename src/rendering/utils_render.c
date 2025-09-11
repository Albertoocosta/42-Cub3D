/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:55:37 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 15:14:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_image_pixel(t_cub *cub, int x, int y, int color)
{
	int pixel;

	pixel = y * (cub->mlx.size_line / 4) + x;
	cub->mlx.img_addr[pixel] = color;
}
