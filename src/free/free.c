/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:55:11 by cda-fons          #+#    #+#             */
/*   Updated: 2025/10/01 01:41:37 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void free_tab_int(int **tab, int size)
{
    int i;
    
    if (!tab)
        return;
    i = 0;
    while (i < size)
    {
        if (tab[i])
            free(tab[i]);
        i++;
    }
    free(tab);
}

int	free_data(t_cub *cub)
{
	if (cub->texture.texture_grid)
		free_tab((void **)cub->texture.texture_grid);
	if (cub->texture.pixels_text)
		free_tab((void **)cub->texture.pixels_text);
	//free_texinfo(&data->texinfo);
	//free_map(cub);
	return (1);
}
int	err_msg(char *detail, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}
