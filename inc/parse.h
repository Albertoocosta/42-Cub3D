/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:58:11 by rde-fari          #+#    #+#             */
/*   Updated: 2025/08/22 20:07:34 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3D.h"

// Errors (More errors will be added, depending on the need.)
typedef enum e_error
{
	SUCCESS = 0,
	INVALID_ARG_COUNT
}	t_error;

// Function declaration
void	error_handler(t_error error);
t_error	verify_arguments(int ac, char **av);

#endif