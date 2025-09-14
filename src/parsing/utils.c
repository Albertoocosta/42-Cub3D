/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:16:44 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/14 19:26:33 by rde-fari         ###   ########.fr       */
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

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if (parse_file(fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int check_extension(const char *path, char *extension)
{
	int len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, extension, 4) == 0);
}

int ft_is_map_line(char *line)
{
	int i = 0;

	while (line[i] && ft_is_space(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == '0'
			|| line[i] == '1'
			|| line[i] == 'N'
			|| line[i] == 'S'
			|| line[i] == 'E'
			|| line[i] == 'W'
			|| line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int ft_is_empty_line(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}



int parse_file(int fd)
{
	char *line;
	int map_started = 0;

	while ((line = get_next_line(fd)))
{
	if (ft_is_empty_line(line))
	{
		free(line);
		continue ;
	}
	if (ft_is_map_line(line))
		map_started = 1;
	else
	{
		if (map_started)
		{
			free(line);
			return (printf("Error!\nMap must be the last element.\n"), 1);
		}
	}
	free(line);
}
	return (0);
}
