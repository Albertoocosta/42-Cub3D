/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:21:24 by alberto           #+#    #+#             */
/*   Updated: 2025/11/24 15:41:26 by rde-fari         ###   ########.fr       */
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

// Project
# define MOVESPEED 0.0125
# define ROTSPEED 0.015
# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "Cub3D"

enum	e_orientation
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5,
	OTHER = 100
};

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	spawn_dir;
	int		move_x;
	int		move_y;
	int		rotate;
	int		moved;
}	t_player;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		wall_dist;
	double		wall_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
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
	int			*img_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}	t_mlx;

typedef struct s_map
{
	char		**map;
	int			map_w;
	int			map_h;
}	t_map;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	bool		has_no;
	bool		has_so;
	bool		has_we;
	bool		has_ea;
	bool		has_floor;
	bool		has_ceil;
	double		step;
	double		pos;
	int			floor_rgb[3];
	int			ceil_rgb[3];
	int			floor_hex;
	int			ceil_hex;
	int			size;
	int			index;
	int			texture_x;
	int			texture_y;
	int			**pixels_text;
	int			**texture_grid;
}	t_texture;

typedef struct s_cub
{
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;
	t_texture	texture;
	t_map		map;
}	t_cub;

typedef struct s_flood
{
	int			x;
	int			y;
}				t_flood;

int		parser(int ac, char **av, t_cub *cub);
int		check_extension(const char *file, char *extension);
int		parse_input(const char *file, t_cub *cub);
int		parse_config(t_cub *cub, int fd);
int		validate_config(t_cub *cub);
int		parse_config_line(char *line, t_texture *texture);
int		parse_texture(char *line, char **path, bool *has_flag);
int		parse_map(const char *file, t_cub *cub);
int		read_map_lines(int fd, char ***map_lines, int *line_count);
void	init_cub(t_cub *cub);
int		parse_color(const char *str, int rgb[3], bool *has_flag);
void	rgb_to_hex(t_texture *texture);
int		ft_is_map_line(char *line);
int		map_on_bottom(const char *file);
int		ft_is_empty_line(char *line);
int		parse_file(int fd);
int		ft_is_space(char c);
void	free_structs(t_cub *cub);
void	calculate_map_dimensions(t_cub *cub, char **map_lines, int count);
void	set_player_position(t_cub *cub, int x, int y, char dir);
void	error_msg(char *str);
int		validate_map_boundaries(t_cub *cub);
int		flood_fill_validation(t_cub *cub);
int		check_map_continuity(char **map_lines, int line_count);
void	free_map_lines(char **map_lines, int line_count);
int		add_map_line(char ***map_lines, int *line_count, char *line);
int		is_valid_map_char(char c);
int		find_player(t_cub *cub);
void	flood_fill(t_cub *cub, char **map_copy, t_flood pos, int *invalid);

//Raycasting
void	fill_ray(int x, t_ray *ray, t_player *player);
void	set_dda(t_ray *ray, t_player *player);
void	run_dda(t_cub *cub, t_ray *ray);
void	line_height_calc(t_ray *ray, t_player *player);
int		raycasting(t_player *player, t_cub *cub);
void	rendering_ray(t_cub *cub);
int		rendering(t_cub *cub);
void	init_texture_pixel(t_cub *cub);
void	update_pixel(t_cub *cub, t_texture *tex, t_ray *ray, int x);
void	load_textures(t_cub *cub);
void	load_texture_image(t_cub *cub, int index, char *path);
int		set_mlx(t_cub *cub);
void	init_img(t_cub *cub, int width, int height);
int		validate_move(t_cub *cub, double new_x, double new_y);
int		rotate_player(t_cub *cub, double rotdir);
void	set_image_pixel(t_cub *cub, int x, int y, int color);
int		move_player(t_cub *cub);
void	init_ray(t_ray *ray);
int		key_release_handler(int key, t_cub *cub);
int		key_press_handler(int key, t_cub *cub);
void	initial_player_direction(t_cub *cub);
int		free_data(t_cub *cub);
void	clean_exit(t_cub *data, int code);
int		exit_cub3d(t_cub *cub);
void	free_tab(void **tab);
void	free_tab_int(int **tab, int size);

//map_chars
int		check_map(char *line);
int		is_config_line(char *line);

#endif