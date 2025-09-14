/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:10:51 by alberto           #+#    #+#             */
/*   Updated: 2025/09/12 19:38:49 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool wall_collision(t_cub *cub, double x, double y)
{
	if (cub->map.map[(int)x][(int)y] == '0')
		return (true);
	return (false);
}

bool valid_position_in_map(t_cub *cub, double x, double y)
{
	if (x < 0.25 || x >= cub->map.map_w - 1.25)
		return (false);
	if (y < 0.25 || y >= cub->map.map_h - 0.25)
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