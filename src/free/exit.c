/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:37:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 01:44:36 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	clean_exit(t_cub *cub, int code)
{
	if (!cub)
		exit(code);
	if (cub->mlx.win_ptr && cub->mlx.mlx_ptr)
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	if (cub->mlx.mlx_ptr)
	{
		mlx_destroy_display(cub->mlx.mlx_ptr);
		mlx_loop_end(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
	}
	//free(cub);
	exit(code);
}

int	exit_cub3d(t_cub *cub)
{
	clean_exit(cub, 0);
	return (0);
}