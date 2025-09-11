/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:58:11 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/11 13:31:20 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

// Não incluir cub3D.h aqui para evitar recursão

// Todas as structs principais agora estão em cub3D.h (t_cub, t_player, t_texture, etc)
// Funções de inicialização e parsing agora usam t_cub diretamente

void init_cub(t_cub *cub);
int parser(int ac, char **av, t_cub *cub);
int check_extension(const char *file, char *extension);
int parse_input(const char *file, t_cub *cub);
int parse_config(t_cub *cub, int fd);
int	validate_config(t_cub *cub);
int parse_config_line(char *line, t_texture *texture);
int parse_texture(char *line, char **path, bool *has_flag);

int parse_color(const char *str, int rgb[3]);
int parse_map(t_cub *cub, int fd);
int parse_color(const char *str, int rgb[3]);

#endif