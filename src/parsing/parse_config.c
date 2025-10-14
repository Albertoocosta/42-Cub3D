/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:48 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/14 16:56:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_config(t_cub *cub, int fd)
{
	char	*line;

	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_config_line(line, &cub->texture))
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_config_line(char *line, t_texture *texture)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		return (parse_texture(line + 2, &texture->no_path, &texture->has_no));
	if (ft_strncmp(line, "SO", 2) == 0)
		return (parse_texture(line + 2, &texture->so_path, &texture->has_so));
	if (ft_strncmp(line, "WE", 2) == 0)
		return (parse_texture(line + 2, &texture->we_path, &texture->has_we));
	if (ft_strncmp(line, "EA", 2) == 0)
		return (parse_texture(line + 2, &texture->ea_path, &texture->has_ea));
	if (ft_strncmp(line, "F", 1) == 0)
		return (parse_color(line + 1, texture->floor_rgb, &texture->has_floor));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_color(line + 1, texture->ceil_rgb, &texture->has_ceil));
	rgb_to_hex(texture);
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

int	parse_color(const char *str, int rgb[3], bool *has_flag)
{
	char	**char_rgb;
	int		i;

	if (*has_flag)
		return (printf("Erro!\nDuplicated RGB.\n"), 1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (!ft_isrgb(str))
		return (printf("Erro!\nInvalid RGB format.\n"), 1);
	char_rgb = ft_split(str, ',');
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(char_rgb[i]) >= 0 && ft_atoi(char_rgb[i]) <= 255)
			rgb[i] = ft_atoi(char_rgb[i]);
		else
		{
			free_splits(char_rgb);
			return (printf("Erro!\nInvalid RGB color.\n"), 1);
		}
		i++;
	}
	*has_flag = true;
	free_splits(char_rgb);
	return (0);
}
