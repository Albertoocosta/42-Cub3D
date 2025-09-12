/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:09:58 by alberto           #+#    #+#             */
/*   Updated: 2025/09/12 19:31:38 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* 
As direções NO/SO/WE/EA são representadas dessa maneira apenas para a textura.
Quando tiver recebendo "player->direction" é representado como N/S/E/W.
além disso, na estrutura, o tipo de variável que armazena essa informação é apenas um "char", e não um "char *".
*/

void initial_NO_SO(t_player *player)
{
	if (player->spawn_dir == SO)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->spawn_dir == NO)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

void initial_EA_WE(t_player *player)
{
	if (player->spawn_dir == WE)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (player->spawn_dir == EA)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else
		return;
}

void initial_player_direction(t_cub *cub)
{
	initial_NO_SO(&cub->player);
	initial_EA_WE(&cub->player);
}