/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:11:08 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 15:19:09 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int rotate_left_right(t_cub *cub, double rotspeed)
{
	t_player *player;
	double tmp_x;

	player = &cub->player;
	tmp_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotspeed) - player->dir_y * sin(rotspeed);
	player->dir_y = tmp_x * sin(rotspeed) + player->dir_y * cos(rotspeed);
	tmp_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotspeed) - player->plane_y * sin(rotspeed);
	player->plane_y = tmp_x * sin(rotspeed) + player->plane_y * cos(rotspeed);
	return (1);
}

int rotate_player(t_cub *cub, double rotdir)
{
	int moved;
	double rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_left_right(cub, rotspeed);
	return (moved);
}
