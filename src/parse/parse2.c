/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:49:37 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 16:49:50 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_north_values(t_map *map)
{
	map->player->dir = 'N';
	map->player->dir_x = 0.0;
	map->player->dir_y = -1.0;
	map->player->plane_x = 0.66;
	map->player->plane_y = 0.0;
}

void	init_south_values(t_map *map)
{
	map->player->dir = 'S';
	map->player->dir_x = 0.0;
	map->player->dir_y = 1.0;
	map->player->plane_x = -0.66;
	map->player->plane_y = 0.0;
}

void	init_east_values(t_map *map)
{
	map->player->dir = 'E';
	map->player->dir_x = 1.0;
	map->player->dir_y = 0.0;
	map->player->plane_x = 0.0;
	map->player->plane_y = 0.66;
}

void	init_west_values(t_map *map)
{
	map->player->dir = 'W';
	map->player->dir_x = -1.0;
	map->player->dir_y = 0.0;
	map->player->plane_x = 0.0;
	map->player->plane_y = -0.66;
}
