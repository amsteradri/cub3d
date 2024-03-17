/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:27:26 by isromero          #+#    #+#             */
/*   Updated: 2024/03/17 10:43:28 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_camera_left(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->player->dir_x;
	map->player->dir_x = map->player->dir_x * cos(-(16 * DR))
		- map->player->dir_y * sin(-(16 * DR));
	map->player->dir_y = old_dir_x * sin(-(16 * DR)) + map->player->dir_y
		* cos(-(16 * DR));
	old_plane_x = map->player->plane_x;
	map->player->plane_x = map->player->plane_x * cos(-(16 * DR))
		- map->player->plane_y * sin(-(16 * DR));
	map->player->plane_y = old_plane_x * sin(-(16 * DR)) + map->player->plane_y
		* cos(-(16 * DR));
}

void	move_camera_right(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->player->dir_x;
	map->player->dir_x = map->player->dir_x * cos(16 * DR) - map->player->dir_y
		* sin(16 * DR);
	map->player->dir_y = old_dir_x * sin(16 * DR) + map->player->dir_y
		* cos(16 * DR);
	old_plane_x = map->player->plane_x;
	map->player->plane_x = map->player->plane_x * cos(16 * DR)
		- map->player->plane_y * sin(16 * DR);
	map->player->plane_y = old_plane_x * sin(16 * DR) + map->player->plane_y
		* cos(16 * DR);
}

int	is_valid_move(int fil, int col, t_map *map)
{
	double	margin;

	margin = 0.4;
	if (fil < margin || fil >= map->y - margin || col < margin || col >= map->x
		- margin)
		return (0);
	
	// if (map->map[fil + 1][col] == 'o' ||  map->map[fil][col + 1] == 'o' || map->map[fil - 1][col] == 'o' ||  map->map[fil][col - 1] == 'o'
	//  || map->map[fil + 1][col + 1] == 'o' ||  map->map[fil - 1][col - 1] == 'o') 
	// 	map->map[fil][col] = 'c';
	
	if (map->map[fil][col] == '1' || map->map[fil][col] == 'c')
		return (0);
	return (1);
}
