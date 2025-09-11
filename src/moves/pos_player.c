/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:10:51 by alberto           #+#    #+#             */
/*   Updated: 2025/09/11 18:02:34 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool wall_collision(t_cub *cub, double x, double y)
{
	int new_x;
	int new_y;

	new_x = (int)x;	 
	new_y = (int)y;
	if (new_y < 0 || new_y >= cub->map_h
		|| new_x < 0 || new_x >= cub->map_w)
        return (true);
	if (cub->map[new_x][new_y] == '1')
		return (true);
	return (false);
}

bool valid_position_in_map(t_cub *cub, double x, double y)
{
	if (x < 0.25 || x >= cub->map_w - 1.25)
		return (false);
	if (y < 0.25 || y >= cub->map_h - 0.25)
		return (false);
	return (true);
}

bool valid_position(t_cub *cub, double x, double y)
{
	if (valid_position_in_map(cub, x, y))
		return (true);
	if (wall_collision(cub, x, y))
		return (true);
	return (false);
}

int validate_move(t_cub *cub, double new_x, double new_y)
{
	int moved;

	moved = 0;
	if (valid_position(cub, new_x, cub->player.pos_y))
	{
		cub->player.pos_x = new_x;
		moved = 1;
	}
	if (valid_position(cub, cub->player.pos_x, new_y))
	{
		cub->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}