/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:16:44 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/14 15:18:50 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void rgb_to_hex(t_texture *texture)
{
	texture->floor_hex = texture->floor_rgb[0] << 16 | texture->floor_rgb[1] << 8 | texture->floor_rgb[2];
	texture->ceil_hex = texture->ceil_rgb[0] << 16 | texture->ceil_rgb[1] << 8 | texture->ceil_rgb[2];
}

int map_on_bottom(const char *file)
{
	int fd;
	char *line;
	bool map_found = false;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)))
	{
		if (!map_found)
		{
			if (!is_map_line(line))
			map_found = true;
		}
		printf("map_found = %s\n", (map_found? "TRUE" : "FALSE"));
		if (map_found && is_map_line(line))
		{
			free(line);
			close(fd);
			return (printf("Erro!\nInvalid map formatting."), 1);
		}
		free(line);
	}
	close(fd);
	return (0);
}

/*
	Abre
	file_found = false
	Para cada linha do mapa:
		linha = remove_spaces
		Se ainda não encontrou o mapa:
			Se a linha parece linha do mapa:
				found_map = true;
			Se não (Já encontrou o mapa)
				se é uma linha vazia: continua
				se não e nada do mapa: erro
	se map_found = false: erro
	success;
*/

bool is_map_line(const char *line)
{
	int i = 0;
	
	while (line[i])
	{
		if (!strchr("01NSEW ", line[i]))
			return (false);
		i++;
	}
	return (true);
}

int check_extension(const char *path, char *extension)
{
	int len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, extension, 4) == 0);
}
