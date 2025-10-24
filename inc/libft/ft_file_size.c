/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:49:12 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/24 18:09:25 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_file_size(const char *path)
{
	int		fd;
	int		total_size;
	char	*line;

	line = NULL;
	total_size = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		total_size++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (total_size);
}
