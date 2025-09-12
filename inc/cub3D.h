/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:21:24 by alberto           #+#    #+#             */
/*   Updated: 2025/09/12 19:39:16 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>

// MINILIBX
#include <X11/keysym.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "./Minilibx/mlx.h"
#include "./Minilibx/mlx_int.h"

// Libft
#include "./libft/libft.h"

typedef struct s_texture t_texture;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_mlx t_mlx;
typedef struct s_cub t_cub;
typedef struct s_map t_map;

// Project
#include "parse.h"
#include "raycasting.h"

#define MOVESPEED 0.0125
#define ROTSPEED 0.015
#define WIDTH 800
#define HEIGHT 600
#define WIN_TITLE "Fucking Hellcife CUB3D"

enum orientation
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5,
	OTHER = 100
};

typedef struct s_texture
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	bool has_no;
	bool has_so;
	bool has_we;
	bool has_ea;
	bool has_floor;
	bool has_ceil;
	int floor_rgb[3];
	int ceil_rgb[3];
	int floor_hex;
	int ceil_hex;
	int size;
	int index;
	int texture_x;
	int texture_y;
} t_texture;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	char spawn_dir;
	int move_x;
	int move_y;
	int rotate;
	int moved;
} t_player;

typedef struct s_ray
{
	double camera_x;
	double dir_x;
	double dir_y;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	double sidedist_x;
	double sidedist_y;
	double deltadist_x;
	double deltadist_y;
	double wall_dist;
	double wall_x;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
} t_ray;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int *img_addr;
	int bits_per_pixel;
	int size_line;
	int endian;
} t_mlx;

typedef struct s_map
{
	char **map;
	int map_w;
	int map_h;
} t_map;

typedef struct s_cub
{
	t_mlx mlx;
	t_player player;
	t_ray ray;
	t_texture texture;
	t_map map;
} t_cub;

#endif