/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/15 17:33:39 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycast(t_map *map)
{
	map->ray->col = -1;
	while (++map->ray->col < map->screen_width)
	{
		double camera_x = 2.0 * map->ray->col / (double)map->screen_width - 1.0;
		map->ray->dir_x = map->player->dir_x + map->player->plane_x * camera_x;
		map->ray->dir_y = map->player->dir_y + map->player->plane_y * camera_x;

		map->ray->map_x = (int)map->player->x;
		map->ray->map_y = (int)map->player->y;

		if (map->ray->dir_x == 0)
			map->ray->delta_dist_x = INFINITY;
		else
			map->ray->delta_dist_x = fabs(1 / map->ray->dir_x);
		if (map->ray->dir_y == 0)
			map->ray->delta_dist_y = INFINITY;
		else
			map->ray->delta_dist_y = fabs(1 / map->ray->dir_y);

		// Calculate step and initial sideDist
		if (map->ray->dir_x < 0)
		{
			map->ray->step_x = -1;
			map->ray->side_dist_x = (map->player->x - (float)map->ray->map_x)
				* map->ray->delta_dist_x;
		}
		else
		{
			map->ray->step_x = 1;
			map->ray->side_dist_x = ((float)map->ray->map_x + 1.0
					- map->player->x) * map->ray->delta_dist_x;
		}
		if (map->ray->dir_y < 0)
		{
			map->ray->step_y = -1;
			map->ray->side_dist_y = (map->player->y - map->ray->map_y)
				* map->ray->delta_dist_y;
		}
		else
		{
			map->ray->step_y = 1;
			map->ray->side_dist_y = (map->ray->map_y + 1.0 - map->player->y)
				* map->ray->delta_dist_y;
		}

		// DDA
		int hit = 0;
		while (hit == 0)
		{
			if (map->ray->side_dist_x < map->ray->side_dist_y)
			{
				map->ray->side_dist_x += map->ray->delta_dist_x;
				map->ray->map_x += map->ray->step_x;
				if (map->ray->step_x == -1)
					map->ray->side = WEST;
				else
					map->ray->side = EAST;
			}
			else
			{
				map->ray->side_dist_y += map->ray->delta_dist_y;
				map->ray->map_y += map->ray->step_y;
				if (map->ray->step_y == -1)
					map->ray->side = NORTH;
				else
					map->ray->side = SOUTH;
			}
			// Check if ray has hit a wall
			if (map->map[map->ray->map_y][map->ray->map_x] == '1')
				hit = 1;
		}

		if (map->ray->side == EAST || map->ray->side == WEST)
			map->ray->perp_wall_dist = map->ray->side_dist_x
				- map->ray->delta_dist_x;
		else if (map->ray->side == NORTH || map->ray->side == SOUTH)
			map->ray->perp_wall_dist = map->ray->side_dist_y
				- map->ray->delta_dist_y;
		/* draw_image(map); */

		// Con texturas (haciendo)
		calculate_draw_values(map);
		draw_textures(map);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return (0);
}