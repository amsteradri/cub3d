/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:36:06 by isromero          #+#    #+#             */
/*   Updated: 2023/12/23 14:36:26 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_perpendicular_distance(t_map *map)
{
	if (map->ray->side == EAST || map->ray->side == WEST)
			map->ray->perp_wall_dist = map->ray->side_dist_x
				- map->ray->delta_dist_x;
	else if (map->ray->side == NORTH || map->ray->side == SOUTH)
			map->ray->perp_wall_dist = map->ray->side_dist_y
				- map->ray->delta_dist_y;
}

