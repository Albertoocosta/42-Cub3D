/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:17:40 by alberto           #+#    #+#             */
/*   Updated: 2025/10/20 18:20:19 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parser(ac, av, &cub))
		return (1);
	if (set_mlx(&cub))
		return (1);
	cub.texture.size = 64;
	load_textures(&cub);
	cub.player.moved = 1;
	mlx_loop_hook(cub.mlx.mlx_ptr, rendering, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	clean_exit(&cub, 0);
	return (0);
}

// int main(void)
// {
// 	void	*mlx;
// 	void	*win;
// 	void	*img;

// 	mlx = mlx_init();
// 	if (!mlx)
// 		return (1);

// 	win = mlx_new_window(mlx, 200, 200, "Leak Test");
// 	if (!win)
// 		return (free(mlx), 1);

// 	img = mlx_new_image(mlx, 200, 200);
// 	if (!img)
// 		return (mlx_destroy_window(mlx, win), free(mlx), 1);

// 	// Destrói tudo corretamente
// 	mlx_destroy_image(mlx, img);
// 	mlx_destroy_window(mlx, win);
// 	mlx_destroy_display(mlx);
// 	free(mlx);

// 	return (0);
// }


// int main(void)
// {
// 	void *mlx = mlx_init();
// 	void *win = mlx_new_window(mlx, 800, 600, "Test");
// 	void *img = mlx_new_image(mlx, 800, 600);
	
// 	mlx_destroy_image(mlx, img);
// 	mlx_destroy_window(mlx, win);
// 	mlx_destroy_display(mlx);
// 	free(mlx);
// 	return (0);
// }