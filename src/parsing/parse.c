/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:11:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/14 19:34:22 by rde-fari         ###   ########.fr       */
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
		|| map_on_bottom(av[1]))
		return (1);
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

int	validate_config(t_cub *cub)
{
	int	fd;

	fd = 0;
	if (!cub->texture.has_no || !cub->texture.has_so
		|| !cub->texture.has_we || !cub->texture.has_ea
		|| !cub->texture.has_ceil || !cub->texture.has_floor)
		return (printf("Erro!\nMissing configuration."), 1);
	fd = open(cub->texture.no_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing North texture file."), 1);
	close(fd);
	fd = open(cub->texture.so_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing South texture file."), 1);
	close(fd);
	fd = open(cub->texture.we_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing West texture file."), 1);
	close(fd);
	fd = open(cub->texture.ea_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing East texture file."), 1);
	close(fd);
	return (0);
}
