/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/09/14 15:43:09 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	t_cub cub;

	if (parser(ac, av, &cub))
		return (1);
		
	if (set_mlx(&cub))
		return (1);
	mlx_loop_hook (cub.mlx.mlx_ptr, rendering, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	printf("all clear and running!");
	return (0);
}
