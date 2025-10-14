/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:11:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/14 16:56:39 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parser(int ac, char **av, t_cub *cub)
{
	if (ac != 2 || !check_extension(av[1], ".cub"))
		return (printf("Error\nInvalid program usage.\n"), 1);
	init_cub(cub);
	if (parse_input(av[1], cub)
		|| validate_config(cub)
		|| map_on_bottom(av[1])
		|| parse_map(av[1], cub))
		return (1);
	initial_player_direction(cub);
	return (0);
}

int	parse_input(const char *file, t_cub *cub)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Erro!\nUnable to open map file."), 1);
	if (parse_config(cub, fd))
		return (1);
	close(fd);
	return (0);
}

static int	validate_texture_file(char *path, char *name)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Erro!\nInvalid or missing %s texture file.", name);
		return (1);
	}
	close(fd);
	return (0);
}

static int	check_all_configs(t_cub *cub)
{
	if (!cub->texture.has_no || !cub->texture.has_so
		|| !cub->texture.has_we || !cub->texture.has_ea
		|| !cub->texture.has_ceil || !cub->texture.has_floor)
		return (printf("Erro!\nMissing configuration."), 1);
	return (0);
}

int	validate_config(t_cub *cub)
{
	if (check_all_configs(cub))
		return (1);
	if (validate_texture_file(cub->texture.no_path, "North"))
		return (1);
	if (validate_texture_file(cub->texture.so_path, "South"))
		return (1);
	if (validate_texture_file(cub->texture.we_path, "West"))
		return (1);
	if (validate_texture_file(cub->texture.ea_path, "East"))
		return (1);
	return (0);
}
