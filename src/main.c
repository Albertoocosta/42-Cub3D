/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/08/26 17:51:32 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub		cub;

	//error_code = verify_arguments(ac, av);
	if (ac != 2)
	{
		errorHandler(INVALID_USAGE);
		return (1);
	}
	(void)av;
	printf("all clear and running!");
	//inicia tudo a 0.
	ft_bzero(&cub, sizeof(cub));
	
	/* ***** DEIXEI TUDO COMENTADO PARA AJUSTAR DEPOIS ****** */
	
	
	if (set_mlx(&cub))
		return (1);
	//falta criar as funcoes para os hooks
	mlx_loop_hook (cub.mlx.mlx_ptr, rendering, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	return (0);
}
