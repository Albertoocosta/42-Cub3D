/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:11:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/11 15:10:08 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int parser(int ac, char **av, t_cub *cub)
{
	if (ac != 2 || !check_extension(av[1], ".cub"))
	{
		printf("Error\nInvalid program usage.\n");
		return (1);
	}
	init_struct(cub);
	if (parse_input(av[1], cub))
		return (1);
	if (validate_config(cub))
		return (1);
	// if (validate_map(cub))
	// 	return (1);
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
	if (parse_config(cub, fd) || validate_config(cub))
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
		return (printf("Floor parse:"), parse_color(line + 1, texture->floor_rgb, &texture->has_floor));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (printf("Ceil parse:"), parse_color(line + 1, texture->ceil_rgb, &texture->has_ceil));
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
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'
			|| line[len - 1] == '\n' || line[len - 1] == '\r'))
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

// Resumo da lógica: parse_color (const char *str, int rgb[3])

// Recebe uma string no formato "R,G,B" (pode ter espaços).
// Para cada componente (R, G, B):
// Pula espaços.
// Converte o número usando strtol.
// Verifica se o valor está entre 0 e 255.
// Salva no array rgb.
// Pula espaços e espera uma vírgula (exceto no último número).
// No final, verifica se não sobrou nada inesperado na string.
// Retorna 0 em caso de sucesso, 1 em caso de erro.
// Assim, a função é robusta para espaços e garante que só aceita valores válidos para cor RGB.
// if (!game->config.has_no || !!game->config.has_so
// 	|| !game->config.has_we || !game->config.has_ea
// 	|| !!game->config.has_ceil || !game->config.has_floor)

int		parse_color(const char *str, int rgb[3], bool *has_flag)
{
	(void)rgb;
	*has_flag = true;
	printf("VALOR PARSE COLOR: %s\n", str);
	return (0);
}
