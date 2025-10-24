/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:58:11 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 17:19:14 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "cub3D.h"

int parser(int ac, char **av, t_cub *cub);
int check_extension(const char *file, char *extension);
int parse_input(const char *file, t_cub *cub);
int parse_config(t_cub *cub, int fd);
int validate_config(t_cub *cub);
int parse_config_line(char *line, t_texture *texture);
int parse_texture(char *line, char **path, bool *has_flag);
int parse_map(const char *file, t_cub *cub);
int read_map_lines(int fd, char ***map_lines, int *line_count);
void init_cub(t_cub *cub);
int parse_color(const char *str, int rgb[3], bool *has_flag);
void rgb_to_hex(t_texture *texture);
int ft_is_map_line(char *line);
int map_on_bottom(const char *file);
int ft_is_empty_line(char *line);
int parse_file(int fd);
int ft_is_space(char c);
void free_structs(t_cub *cub);
void calculate_map_dimensions(t_cub *cub, char **map_lines, int count);
void set_player_position(t_cub *cub, int x, int y, char dir);
void error_msg(char *str);
int validate_map_boundaries(t_cub *cub);
int flood_fill_validation(t_cub *cub);
int check_map_continuity(char **map_lines, int line_count);
void free_map_lines(char **map_lines, int line_count);

#endif