/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/10/23 19:40:10 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parser(ac, av, &cub) || set_mlx(&cub))
		clean_exit(&cub, 1);
	cub.texture.size = 64;
	load_textures(&cub);
	cub.player.moved = 1;
	mlx_loop_hook(cub.mlx.mlx_ptr, rendering, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	clean_exit(&cub, 0);
	return (0);
}
