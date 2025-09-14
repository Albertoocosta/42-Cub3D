/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:58:11 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/14 15:37:01 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "cub3D.h"

typedef struct s_map
{
	char **map;
	int map_w;
	int map_h;
} t_map;

typedef struct s_texture
{
	char 	*no_path;
	char 	*so_path;
	char 	*we_path;
	char 	*ea_path;
	bool	has_no;
	bool	has_so;
	bool	has_we;
	bool 	has_ea;
	bool 	has_floor;
	bool 	has_ceil;
	double 	step;
	double	pos;
	int 	floor_rgb[3];
	int 	ceil_rgb[3];
	int 	floor_hex;
	int 	ceil_hex;
	int 	size;
	int 	index;
	int 	texture_x;
	int 	texture_y;
	int		**pixels_text;
	int		**texture_grid;
} t_texture;


int parser(int ac, char **av, t_cub *cub);
int check_extension(const char *file, char *extension);
int parse_input(const char *file, t_cub *cub);
int parse_config(t_cub *cub, int fd);
int validate_config(t_cub *cub);
int parse_config_line(char *line, t_texture *texture);
int parse_texture(char *line, char **path, bool *has_flag);

int parse_map(t_cub *cub, int fd);
void init_cub(t_cub *cub);

int parse_color(const char *str, int rgb[3], bool *has_flag);
void rgb_to_hex(t_texture *texture);

int	ensure_bottom_map(t_map *map, char *file);

#endif