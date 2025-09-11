/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:09:12 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 17:59:35 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	printf("Dentro do move_player -> Move X: %d, Move Y: %d, Rotate: %d\n", cub->player.move_x, cub->player.move_y, cub->player.rotate);
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