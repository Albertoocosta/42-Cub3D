/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:53:47 by alberto           #+#    #+#             */
/*   Updated: 2025/08/26 16:07:05 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

int		raycasting(t_player *player, t_cub *cub);
int		rendering (t_cub *cub);
void		init_ray(t_ray *ray);

#endif