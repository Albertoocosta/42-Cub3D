/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:11:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/13 17:39:23 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool is_map_line(const char *line);
static int map_on_bottom(const char *file);

int parser(int ac, char **av, t_cub *cub)
{
	if (ac != 2 || !check_extension(av[1], ".cub"))
		return (printf("Error\nInvalid program usage.\n"), 1);
	init_cub(cub);
	if (parse_input(av[1], cub) || validate_config(cub))
		return (1);
	if (map_on_bottom(av[1]))
		return (1);
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

int parse_input(const char *file, t_cub *cub)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Erro!\nUnable to open map file."), 1);
	if (parse_config(cub, fd))
		return (1);
	close(fd);
	return (0);
}

int parse_config(t_cub *cub, int fd)
{
	char *line;

	line = NULL;
	while ((line = get_next_line(fd)))
	{
		if (parse_config_line(line, &cub->texture))
			return (1);
		free(line);
	}
	return (0);
}

int parse_config_line(char *line, t_texture *texture)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return parse_texture(line + 2, &texture->no_path, &texture->has_no);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return parse_texture(line + 2, &texture->so_path, &texture->has_so);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return parse_texture(line + 2, &texture->we_path, &texture->has_we);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return parse_texture(line + 2, &texture->ea_path, &texture->has_ea);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line + 1, texture->floor_rgb, &texture->has_floor));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line + 1, texture->ceil_rgb, &texture->has_ceil));
	rgb_to_hex(texture);
	return (0);
}

int parse_texture(char *line, char **path, bool *has_flag)
{
	char *trimmed;
	int len;

	while (*line == ' ' || *line == '\t')
		line++;
	if (*has_flag)
		return (printf("Erro!\nDuplicated texture.\n"), 1);
	free(*path);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t' || line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (printf("Erro!\nFailed to allocate memory for texture.\n"), 1);
	ft_strncpy(trimmed, line, len);
	trimmed[len] = '\0';
	*path = trimmed;
	if (!check_extension(*path, ".xpm"))
		return (printf("Erro!\nTexture must be a '.xpm' file."), 1);
	*has_flag = true;
	return (0);
}

int validate_config(t_cub *cub)
{
	int fd;

	fd = 0;
	if (!cub->texture.has_no || !cub->texture.has_so || !cub->texture.has_we || !cub->texture.has_ea || !cub->texture.has_ceil || !cub->texture.has_floor)
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

int parse_color(const char *str, int rgb[3], bool *has_flag)
{
	char **char_rgb;
	int i;

	if (*has_flag)
		return (printf("Erro!\nDuplicated RGB.\n"), 1);
	char_rgb = ft_split(str, ',');
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(char_rgb[i]) >= 0 && ft_atoi(char_rgb[i]) <= 255)
			rgb[i + 1] = ft_atoi(char_rgb[i]);
		else
			return (printf("Erro!\nInvalid RGB color.\n"), 1);
		i++;
	}
	*has_flag = true;
	return (0);
}

void rgb_to_hex(t_texture *texture)
{
	texture->floor_hex = texture->floor_rgb[0] << 16 | texture->floor_rgb[1] << 8 | texture->floor_rgb[2];

	texture->ceil_hex = texture->ceil_rgb[0] << 16 | texture->ceil_rgb[1] << 8 | texture->ceil_rgb[2];
}

static int map_on_bottom(const char *file)
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

static bool is_map_line(const char *line)
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

