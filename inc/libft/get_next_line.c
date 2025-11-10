/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:07:10 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/31 17:34:18 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_from_file(char *g_buffer, int fd)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_check_character(g_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp_buffer);
			if (g_buffer)
				free(g_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		g_buffer = ft_strjoin_gnl(g_buffer, temp_buffer);
	}
	free(temp_buffer);
	return (g_buffer);
}

char	*ft_extract_line(char *g_buffer)
{
	int		i;
	int		k;
	char	*line;

	if (!g_buffer || g_buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (g_buffer[i] != '\n' && g_buffer[i])
		i++;
	k = i;
	if (g_buffer[i] == '\n')
		k++;
	line = ft_calloc_gnl(k + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_strcpy_nl(g_buffer, line, 1);
	return (line);
}

char	*ft_update_data(char *g_buffer)
{
	char	*new_data;
	int		start;

	if (!g_buffer)
		return (NULL);
	start = 0;
	while (g_buffer[start] && g_buffer[start] != '\n')
		start++;
	if (g_buffer[start] == '\0')
	{
		free(g_buffer);
		return (NULL);
	}
	start++;
	new_data = ft_calloc_gnl(ft_strlen_gnl(g_buffer + start) + 1, sizeof(char));
	if (!new_data)
	{
		free(g_buffer);
		return (NULL);
	}
	ft_strcpy_nl(g_buffer + start, new_data, 0);
	free(g_buffer);
	return (new_data);
}

static char	*g_buffer = NULL;

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	g_buffer = ft_read_from_file(g_buffer, fd);
	if (!g_buffer)
		return (NULL);
	line = ft_extract_line(g_buffer);
	if (!line)
	{
		free(g_buffer);
		g_buffer = NULL;
		return (NULL);
	}
	g_buffer = ft_update_data(g_buffer);
	return (line);
}

void	cleanup_gnl(void)
{
	if (g_buffer)
	{
		free(g_buffer);
		g_buffer = NULL;
	}
}
