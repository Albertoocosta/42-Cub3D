/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:55:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/20 17:38:05 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_texture(t_texture *texture)
{
	if (texture->no_path)
		free(texture->no_path);
	if (texture->so_path)
		free(texture->so_path);
	if (texture->we_path)
		free(texture->we_path);
	if (texture->ea_path)
		free(texture->ea_path);
	if (texture->pixels_text)
		free_int_array(texture->pixels_text, HEIGHT);
	if (texture->texture_grid)
		free_int_array(texture->texture_grid, 4);
}

static void	free_map(t_map *map)
{
	if (map)
		free_splits(map->map);
}

void	free_structs(t_cub *cub)
{
	free_texture(&cub->texture);
	free_map(&cub->map);
}
