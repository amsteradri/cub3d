/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/09 11:17:18 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_image(t_map *map, int x)
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
	int line_height = (int)(map->screen_height / map->ray->perp_wall_dist);
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

void	calculate_draw_values(t_map *map)
{
	map->draw->line_height = (int)(map->screen_height / map->ray->perp_wall_dist);
	map->draw->draw_start = -map->draw->line_height / 2 + map->screen_height / 2;
	if (map->draw->draw_start < 0)
		map->draw->draw_start = 0;
	map->draw->draw_end = map->draw->line_height / 2 + map->screen_height / 2;
	if (map->draw->draw_end >= map->screen_height)
		map->draw->draw_end = map->screen_height - 1;
}

int	raycast(t_map *map)
{
	int x;

	x = -1;
	while(++x < map->screen_width)
	{
		double camera_x = 2.0 * x / (double)map->screen_width - 1.0;
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
			map->ray->side_dist_x = (map->player->x - (float)map->ray->map_x) * map->ray->delta_dist_x;
		}
		else
		{
			map->ray->step_x = 1;
			map->ray->side_dist_x = ((float)map->ray->map_x + 1.0 - map->player->x) * map->ray->delta_dist_x;
		}
		if (map->ray->dir_y < 0)
		{
			map->ray->step_y = -1;
			map->ray->side_dist_y = (map->player->y - map->ray->map_y) * map->ray->delta_dist_y;
		}
		else
		{
			map->ray->step_y = 1;
			map->ray->side_dist_y = (map->ray->map_y + 1.0 - map->player->y) * map->ray->delta_dist_y;
		}
		
		// DDA
		int hit = 0;
		while (hit == 0)
		{
			if (map->ray->side_dist_x < map->ray->side_dist_y)
			{
				map->ray->side_dist_x += map->ray->delta_dist_x;
				map->ray->map_x += map->ray->step_x;
				map->ray->side = 0;
			}
			else
			{
				map->ray->side_dist_y += map->ray->delta_dist_y;
				map->ray->map_y += map->ray->step_y;
				map->ray->side = 1;
			}
			// Check if ray has hit a wall
			if (map->map[map->ray->map_y][map->ray->map_x] == '1')
				hit = 1;
		}

		if (map->ray->side == 0)
			map->ray->perp_wall_dist = map->ray->side_dist_x - map->ray->delta_dist_x;
		else
			map->ray->perp_wall_dist = map->ray->side_dist_y - map->ray->delta_dist_y;

		draw_image(map, x);
		
		// Con texturas (haciendo)
		/* calculate_draw_values(map); */
		/* draw_textures(map, x); */
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return 0;
}