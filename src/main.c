/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/08/26 02:24:35 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_error		error_code;
	t_cub		cub;

	error_code = verify_arguments(ac, av);
	if (error_code != SUCCESS)
	{
		error_handler(error_code);
		return (EXIT_FAILURE);
	}
	printf("Verificar arquivo log na root do repositório. Programa compilando e rodando sem erros!");
	//inicia tudo a 0.
	ft_bzero(&cub, sizeof(cub));
	
	/* ***** DEIXEI TUDO COMENTADO PARA AJUSTAR DEPOIS ****** */
	
	
	//if (set_mlx(&cub))
	//	return (1);
	//falta criar as funcoes para os hooks
	//mlx_loop_hook (cub.mlx.mlx_ptr, rendering, &cub);
	//mlx_loop(cub.mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
