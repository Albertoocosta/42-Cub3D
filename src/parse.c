/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:11:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/10 18:08:09 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parser(int ac, char **av, t_game *game)
{
	if (ac != 2 || !check_extension(av[1], ".cub"))
	{
		printf("Error\nInvalid program usage.\n");
		return (1);
	}
	init_game(game);
	if (parse_input(av[1], game))
		return (1);
	// if (validate_config(&game->config))
	// 	return (1);
	// if (validate_map(&game->map))
	// 	return (1);
	return (0);
}

int	check_extension(const char *path, char *extension)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, extension, 4) == 0);
}

int	parse_input(const char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Erro!\nUnable to open map file"), 1);
	if (parse_config(game, fd) || validate_config(game))
		return (1);
	close(fd);
	return (0);
}

int	parse_config(t_game *game, int fd)
{
	char	*line;

	line = NULL;
	while ((line = get_next_line(fd)))
	{
		if (parse_config_line(line, &game->config))
			return (1);
		free(line);
	}
	return (0);
}

int	parse_config_line(char *line, t_config *cfg)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return parse_texture(line + 2, &cfg->no_path, &cfg->has_no);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return parse_texture(line + 2, &cfg->so_path, &cfg->has_so);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return parse_texture(line + 2, &cfg->we_path, &cfg->has_we);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return parse_texture(line + 2, &cfg->ea_path, &cfg->has_ea);
	// if (ft_strncmp(line, "F ", 2) == 0)
	// 	return parse_color(line + 1, cfg->floor_rgb, &cfg->has_floor);
	// if (ft_strncmp(line, "C ", 2) == 0)
	// 	return parse_color(line + 1, cfg->ceil_rgb, &cfg->has_ceil);
	return (0);
}

int	parse_texture(char *line, char **path, bool *has_flag)
{
	char	*trimmed;
	int		len;

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

int	validate_config(t_game *game)
{
	int	fd;

	fd = 0;
	if (!game->config.has_no || !game->config.has_so
		|| !game->config.has_we || !game->config.has_ea)
		return (printf("Erro!\nMissing configuration."), 1);
	fd = open(game->config.no_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing North texture file."), 1);
	close(fd);
	fd = open(game->config.so_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing South texture file."), 1);
	close(fd);
	fd = open(game->config.we_path, O_RDONLY);
	if (fd < 0)
		return (printf("Erro!\nInvalid or missing West texture file."), 1);
	close(fd);
	fd = open(game->config.ea_path, O_RDONLY);
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