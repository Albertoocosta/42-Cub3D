/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:18:23 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 15:19:09 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int key_press_handler(int key, t_cub *cub)
{
	// if (key == XK_Escape)
	// 	exit_cub3d(cub);
	if (key == XK_Left)
		cub->player.rotate -= 1;
	if (key == XK_Right)
		cub->player.rotate += 1;
	if (key == XK_w)
		cub->player.move_y = 1;
	if (key == XK_a)
		cub->player.move_x = -1;
	if (key == XK_s)
		cub->player.move_y = -1;
	if (key == XK_d)
		cub->player.move_x = 1;
	return (0);
}

int key_release_handler(int key, t_cub *cub)
{
	// if (key == XK_Escape)
	// 	exit_cub3d();
	if (key == XK_w && cub->player.move_y == 1)
		cub->player.move_y = 0;
	if (key == XK_s && cub->player.move_y == -1)
		cub->player.move_y = 0;
	if (key == XK_a && cub->player.move_x == -1)
		cub->player.move_x = 0;
	if (key == XK_d && cub->player.move_x == 1)
		cub->player.move_x = 0;
	if (key == XK_Left && cub->player.rotate <= 1)
		cub->player.rotate = 0;
	if (key == XK_Right && cub->player.rotate >= -1)
		cub->player.rotate = 0;
	return (0);
}
