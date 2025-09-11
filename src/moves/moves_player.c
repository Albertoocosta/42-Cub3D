/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:09:12 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 15:14:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int move_player_front(t_cub *cub)
{
	double new_x;
	double new_y;

	new_y = cub->player.pos_x - cub->player.dir_x * MOVESPEED;
	new_x = cub->player.pos_y - cub->player.dir_y * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

int move_player_back(t_cub *cub)
{
	double new_x;
	double new_y;

	new_x = cub->player.pos_x - cub->player.dir_x * MOVESPEED;
	new_y = cub->player.pos_y - cub->player.dir_y * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

int move_player_left(t_cub *cub)
{
	double new_x;
	double new_y;

	new_x = cub->player.pos_x - cub->player.dir_x * MOVESPEED;
	new_y = cub->player.pos_y - cub->player.dir_y * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

int move_player_right(t_cub *cub)
{
	double new_x;
	double new_y;

	new_x = cub->player.pos_x - cub->player.dir_x * MOVESPEED;
	new_y = cub->player.pos_y - cub->player.dir_y * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

int move_player(t_cub *cub)
{
	int moved;

	moved = 0;
	if (cub->player.move_y == 1)
		moved += move_player_front(cub);
	if (cub->player.move_y == -1)
		moved += move_player_back(cub);
	if (cub->player.move_x == 1)
		moved += move_player_left(cub);
	if (cub->player.move_x == -1)
		moved += move_player_right(cub);
	if (cub->player.rotate != 0)
		moved += rotate_player(cub, cub->player.rotate);
	return (moved);
}