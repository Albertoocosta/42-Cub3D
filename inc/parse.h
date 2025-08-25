/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:58:11 by rde-fari          #+#    #+#             */
/*   Updated: 2025/08/25 01:49:07 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3D.h"

// Errors (More errors will be added, depending on the need.)
typedef enum e_error
{
	SUCCESS = 0,
	INVALID_USAGE,
}	t_error;

// Function declarationvoid	errorHandler(t_error error)
void	errorHandler(t_error error);


#endif