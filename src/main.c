/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/10/14 15:27:31 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Function declarations
void create_debug_map(t_cub *cub);
void print_debug_map(t_cub *cub);

int main(int ac, char **av)
{
	t_cub cub;

	// Check if debug mode is requested
	if (ac == 2 && ft_strcmp(av[1], "--debug") == 0)
	{
		printf("=== DEBUG MODE ===\n");
		init_cub(&cub);
		create_debug_map(&cub);
		print_debug_map(&cub);
	}
	else
	{
		if (parser(ac, av, &cub))
			return (1);
	}
	if (set_mlx(&cub))
		return (1);
	mlx_loop_hook(cub.mlx.mlx_ptr, rendering, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	printf("all clear and running!");
	return (0);
}
