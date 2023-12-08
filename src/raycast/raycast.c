/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/08 11:04:55 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_image(t_map *map, int x, int perpWallDist)
{
	int color_sky = 0xABCDEF;

	if (map->img->bits_per_pixel != 32)
		color_sky = mlx_get_color_value(map->mlx_ptr, color_sky);

	int color_wall = 0x00AA0000;

	if (map->img->bits_per_pixel != 32)
		color_wall = mlx_get_color_value(map->mlx_ptr, color_wall);

	int color_floor = 0x00FF00;

	if (map->img->bits_per_pixel != 32)
		color_floor = mlx_get_color_value(map->mlx_ptr, color_floor);
	int line_height = (int)(map->screen_height / perpWallDist);
	int ceiling_height = -line_height / 2 + map->screen_height / 2;
	if (ceiling_height < 0)
		ceiling_height = 0;
	int floor_height = line_height / 2 + map->screen_height / 2;
	if (floor_height >= map->screen_height)
		floor_height = map->screen_height - 1;
	
	for (int y = 0; y < ceiling_height; y++)
	{
		int pixel = (y * map->img->line_length) + (x * 4);
		

		if (map->img->endian == 1)
		{
			map->img->addr[pixel + 0] = (color_sky >> 24);
			map->img->addr[pixel + 1] = (color_sky >> 16) & 0xFF;
			map->img->addr[pixel + 2] = (color_sky >> 8) & 0xFF;
			map->img->addr[pixel + 3] = (color_sky) & 0xFF;
		}
		else if (map->img->endian == 0)
		{
			map->img->addr[pixel + 0] = (color_sky) & 0xFF;
			map->img->addr[pixel + 1] = (color_sky >> 8) & 0xFF;
			map->img->addr[pixel + 2] = (color_sky >> 16) & 0xFF;
			map->img->addr[pixel + 3] = (color_sky >> 24);
		}
	}

	for (int y = ceiling_height; y < floor_height; y++)
	{
		int pixel = (y * map->img->line_length) + (x * 4);
		
		if (map->img->endian == 1)
		{
			map->img->addr[pixel + 0] = (color_wall >> 24);
			map->img->addr[pixel + 1] = (color_wall >> 16) & 0xFF;
			map->img->addr[pixel + 2] = (color_wall >> 8) & 0xFF;
			map->img->addr[pixel + 3] = (color_wall) & 0xFF;
		}
		else if (map->img->endian == 0)
		{
			map->img->addr[pixel + 0] = (color_wall) & 0xFF;
			map->img->addr[pixel + 1] = (color_wall >> 8) & 0xFF;
			map->img->addr[pixel + 2] = (color_wall >> 16) & 0xFF;
			map->img->addr[pixel + 3] = (color_wall >> 24);
		}
	}

	for (int y = floor_height; y < map->screen_height; y++)
	{
		int pixel = (y * map->img->line_length) + (x * 4);
		
		if (map->img->endian == 1)
		{
			map->img->addr[pixel + 0] = (color_floor >> 24);
			map->img->addr[pixel + 1] = (color_floor >> 16) & 0xFF;
			map->img->addr[pixel + 2] = (color_floor >> 8) & 0xFF;
			map->img->addr[pixel + 3] = (color_floor) & 0xFF;
		}
		else if (map->img->endian == 0)
		{
			map->img->addr[pixel + 0] = (color_floor) & 0xFF;
			map->img->addr[pixel + 1] = (color_floor >> 8) & 0xFF;
			map->img->addr[pixel + 2] = (color_floor >> 16) & 0xFF;
			map->img->addr[pixel + 3] = (color_floor >> 24);
		}
	}
}

int	raycast(t_map *map)
{
	int x;

	x = -1;
	while(++x < map->screen_width)
	{
		double camera_x = 2 * x / (double)map->screen_width - 1;
		map->ray->dir_x = map->player->dir_x + map->player->plane_x * camera_x;
		map->ray->dir_y = map->player->dir_y + map->player->plane_y * camera_x;

		int map_x = (int)map->player->x;
		int map_y = (int)map->player->y;

		double side_dist_x;
		double side_dist_y;
		
		double delta_dist_x = (map->ray->dir_x == 0) ? INFINITY : fabs(1 / map->ray->dir_x);
		double delta_dist_y = (map->ray->dir_y == 0) ? INFINITY : fabs(1 / map->ray->dir_y);
		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;

		// Calculate step and initial sideDist
		if (map->ray->dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (map->player->x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - map->player->x) * delta_dist_x;
		}
		if (map->ray->dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (map->player->y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - map->player->y) * delta_dist_y;
		}
		
		// DDA
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				map->ray->side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				map->ray->side = 1;
			}
			// Check if ray has hit a wall
			if (map->map[map_y][map_x] == '1')
				hit = 1;
		}

		if (map->ray->side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		draw_image(map, x, perp_wall_dist);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return 0;
}