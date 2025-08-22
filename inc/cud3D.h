/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cud3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:21:24 by alberto           #+#    #+#             */
/*   Updated: 2025/08/22 11:41:53 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUD3D_H
# define CUD3D_H

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