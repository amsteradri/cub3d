/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/10 15:40:07 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_img_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->img->addr + (y * map->img->line_length
			+ x * (map->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int create_rgb_color(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
}

void	draw_image(t_map *map)
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
		int pixel = (y * map->img->line_length) + (map->ray->col * 4);
	
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
		int pixel = (y * map->img->line_length) + (map->ray->col * 4);
		
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
		int pixel = (y * map->img->line_length) + (map->ray->col * 4);
		
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

void	calculate_tex_x(t_map *map)
{
	int	x;

	x = 0;
	if (map->ray->side == 0)
		map->ray->wall_x = map->player->y + map->ray->perp_wall_dist * map->ray->dir_y;
	else
		map->ray->wall_x = map->player->x + map->ray->perp_wall_dist * map->ray->dir_x;
	map->ray->wall_x -= floor(map->ray->wall_x);
	x = map->ray->wall_x + 64.0;
	map->line->tex_x = (int)x;

	if (map->ray->side == 0 && map->ray->dir_x > 0)
		map->line->tex_x = 64 - map->line->tex_x - 1;
	if (map->ray->side == 1 && map->ray->dir_y < 0)
		map->line->tex_x = 64 - map->line->tex_x - 1;
}

void	draw_wall(t_map *map, int *y, double *step, double *tex_pos)
{
	map->line->tex_y = (int)(*tex_pos) & (64 - 1);
    (*tex_pos) += (*step);

    int tex_offset = (map->line->tex_y * map->textures[0]->line_length) + (map->line->tex_x * (map->textures[0]->bits_per_pixel / 8));
    int texture_color = *(int *)(map->textures[0]->addr + tex_offset);
  
    my_img_pixel_put(map, map->ray->col, *y, texture_color);
}

void	paint_pixels(t_map *map)
{
	double	step;
	int		y;
	double	tex_pos;

	step = 64.0 / map->draw->line_height;
	tex_pos = (map->draw->draw_start - 1900 / 2 + map->draw->line_height / 2) * step;

	y = 0;
	while (y < map->draw->draw_start)
	{
		my_img_pixel_put(map, map->ray->col, y, create_rgb_color(135, 206, 235));
		y++;
	}
	while (y < map->draw->draw_end)
	{
		draw_wall(map, &y, &step, &tex_pos);
		y++;
	}
	while (y < 900)
	{
		my_img_pixel_put(map, map->ray->col, y, create_rgb_color(160, 82, 45));
		y++;
	}
}

int	raycast(t_map *map)
{
	map->ray->col = -1;
	while(++map->ray->col < map->screen_width)
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

		/* draw_image(map); */
		
		// Con texturas (haciendo)
		calculate_draw_values(map);
		calculate_tex_x(map);
		paint_pixels(map);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return 0;
}