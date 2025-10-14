/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:53:47 by alberto           #+#    #+#             */
/*   Updated: 2025/10/14 16:49:57 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "cub3D.h"

// raycasting.c
void	fill_ray(int x, t_ray *ray, t_player *player);
void	set_dda(t_ray *ray, t_player *player);
void	run_dda(t_cub *cub, t_ray *ray);
void	line_height_calc(t_ray *ray, t_player *player);
int		raycasting(t_player *player, t_cub *cub);

// rendering.c
void	rendering_ray(t_cub *cub);
int		rendering(t_cub *cub);
void 	init_texture_pixel(t_cub *cub);
void	update_pixel(t_cub *cub, t_texture *tex, t_ray *ray, int x);
void	load_textures(t_cub *cub);
void	load_texture_image(t_cub *cub, int index, char *path);

// set_mlx.c
int		set_mlx(t_cub *cub);
void	init_img(t_cub *cub, int width, int height);

//movements
int		validate_move(t_cub *cub, double new_x, double new_y);
int		rotate_player(t_cub *cub, double rotdir);
void	set_image_pixel(t_cub *cub, int x, int y, int color);
int		move_player(t_cub *cub);
void	init_ray(t_ray *ray);
int		key_release_handler(int key, t_cub *cub);
int		key_press_handler(int key, t_cub *cub);
void	initial_player_direction(t_cub *cub);

// free

int		free_data(t_cub *cub);
void	clean_exit(t_cub *data, int code);
int		exit_cub3d(t_cub *cub);
void	free_tab(void **tab);
void	free_tab_int(int **tab, int size);
int		err_msg(char *detail, char *str, int code);

//test

int exit_game_test(t_cub *cub);

#endif