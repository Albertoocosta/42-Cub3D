/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:58:11 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/11 11:07:37 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

// Não incluir cub3D.h aqui para evitar recursão

// Structures:
typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_rgb[3];
	int		ceil_rgb[3];
	bool	has_no;
	bool	has_so;
	bool	has_we;
	bool	has_ea;
	bool	has_floor;
	bool	has_ceil;
}	t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
} t_map;

typedef struct s_game
{
	t_config	config;
	t_map		map;
	// mais tarde: mlx_ptr, win_ptr, etc.
	// Esta é a parte em que vamos ter que sincronizar com a estrutura que já existe no ficheiro 'cub3d.h'.
} t_game;

void	init_config(t_config *cfg);
void	init_game(t_game *game);
void	init_map(t_map *map);

int		parser(int ac, char **av, t_game *game);
int		check_extension(const char *file, char *extension);
int		parse_input(const char *file, t_game *game);
int		parse_config(t_game *game, int fd);
int		validate_config(t_game *game);
int		parse_config_line(char *line, t_config *cfg);
int		parse_texture(char *line, char **path, bool *has_flag);

int		parse_color(const char *str, int rgb[3]);
int		parse_map(t_game *game, int fd);

#endif