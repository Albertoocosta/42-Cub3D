/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:11:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/09/10 12:50:03 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parser(int ac, char **av, t_game *game)
{
	if (ac != 2 || !check_extension(av[1]))
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

int	check_extension(const char *file)
{
	int len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

int	parse_input(const char *file, t_game *game)
{
	int fd;

	fd = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Erro\nUnable to open map file"), 1);
	parse_config(game, fd);
	// parse_map(game, fd);
	close(fd);
	return (0);
}

void	parse_config(t_game *game, int fd)
{
	char *line;
	int config = 0;
	int mapl = 0;

	line = NULL;
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
			config++;
		// parse_config_line(line, &game->config);
		else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			mapl++;
		free(line);
	}
	printf("CONFIG LINES: %d.\nMAP LINES: %d.\n", config, mapl);
	(void)game;
}

// int	parse_map(t_game *game, int	fd)
// {

// }

// int	parse_config_line(char *line, t_config *cfg)
// {
// 	while (*line == ' ' || *line == '\t')
// 		line++;
// 	if (ft_strncmp(line, "NO ", 3) == 0)
// 		return parse_texture(line + 2, &cfg->no_path, &cfg->has_no);
// 	if (ft_strncmp(line, "SO ", 3) == 0)
// 		return parse_texture(line + 2, &cfg->so_path, &cfg->has_so);
// 	if (ft_strncmp(line, "WE ", 3) == 0)
// 		return parse_texture(line + 2, &cfg->we_path, &cfg->has_we);
// 	if (ft_strncmp(line, "EA ", 3) == 0)
// 		return parse_texture(line + 2, &cfg->ea_path, &cfg->has_ea);
// 	if (ft_strncmp(line, "F ", 2) == 0)
// 		return parse_color(line + 1, cfg->floor_rgb, &cfg->has_floor);
// 	if (ft_strncmp(line, "C ", 2) == 0)
// 		return parse_color(line + 1, cfg->ceil_rgb, &cfg->has_ceil);
// 	return (0);
// }

int	parse_texture(char *line, char **path, bool *has_flag)
{
	// Pula espaços em branco
	while (*line == ' ' || *line == '\t')
		line++;
	if (*has_flag)
		return (printf("Erro: textura já definida.\n"), 1);
	free(*path);
	*path = ft_strdup(line);
	if (!*path)
	{
		printf("Erro: falha ao alocar memória para o caminho da textura.\n");
		return (1);
	}
	*has_flag = true;
	return (0);
}
