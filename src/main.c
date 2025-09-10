/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/09/10 15:42:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	// t_cub		cub;
	t_game game;

	if (parser(ac, av, &game))
		return (1);
	printf("all clear and running!");

	// ft_bzero(&cub, sizeof(cub));
	// if (set_mlx(&cub))
	// 	return (1);
	// mlx_loop_hook (cub.mlx.mlx_ptr, rendering, &cub);
	// mlx_loop(cub.mlx.mlx_ptr);
	return (0);
}

void	debug(t_game *game)
{
	(void)game;
}