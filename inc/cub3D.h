/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:21:24 by alberto           #+#    #+#             */
/*   Updated: 2025/08/22 19:59:35 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <sys/time.h>

// MINILIBX
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "./Minilibx/mlx.h"
# include "./Minilibx/mlx_int.h"

// Libft
# include "./libft/libft.h"

// Project
# include "parse.h"


typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx_data;

#endif