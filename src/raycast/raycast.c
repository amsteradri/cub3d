/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2024/03/17 10:02:17 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_ray(t_map *map)
{
	double	camera_x;

	camera_x = 2.0 * map->ray->col / (double)map->screen_width - 1.0;
	map->ray->dir_x = map->player->dir_x + map->player->plane_x * camera_x;
	map->ray->dir_y = map->player->dir_y + map->player->plane_y * camera_x;
	map->ray->map_x = (int)map->player->x;
	map->ray->map_y = (int)map->player->y;
}

void	calculate_delta_distance(t_map *map)
{
	if (map->ray->dir_x == 0)
		map->ray->delta_dist_x = INFINITY;
	else
		map->ray->delta_dist_x = fabs(1 / map->ray->dir_x);
	if (map->ray->dir_y == 0)
		map->ray->delta_dist_y = INFINITY;
	else
		map->ray->delta_dist_y = fabs(1 / map->ray->dir_y);
}

void	calculate_side_distance(t_map *map)
{
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
}

void	dda_algorithm(t_map *map)
{
	while (1)
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
		if (map->map[map->ray->map_y][map->ray->map_x] == '1' || map->map[map->ray->map_y][map->ray->map_x] == 'c')
			break ;
	}
}

int	raycast(t_map *map)
{
	map->ray->col = -1;
	while (++map->ray->col < map->screen_width)
	{
		initialize_ray(map);
		calculate_delta_distance(map);
		calculate_side_distance(map);
		dda_algorithm(map);
		calculate_perpendicular_distance(map);
		calculate_draw_values(map);
		draw(map);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return (0);
}
