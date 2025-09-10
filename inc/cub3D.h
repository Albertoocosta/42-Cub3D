/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:21:24 by alberto           #+#    #+#             */
/*   Updated: 2025/09/10 17:48:29 by rde-fari         ###   ########.fr       */
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
# include <assert.h>

// MINILIBX
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "./Minilibx/mlx.h"
# include "./Minilibx/mlx_int.h"

// Libft
# include "./libft/libft.h"

typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_mlx t_mlx;
typedef struct s_cub t_cub;

// Project
# include "parse.h"
# include "raycasting.h"

// Macros
# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "Fucking Hellcife CUB3D"

// Structures
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			move_x;
	int			move_y;
	int			rotate;
}	t_player;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		wall_dist;
	double		wall_x;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*img_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}	t_mlx;

typedef struct s_cub
{
	t_mlx		mlx;
	char		**map;
	int			map_h;
	int			map_w;
	t_player	player;
	t_ray		ray;
}	t_cub;

#endif