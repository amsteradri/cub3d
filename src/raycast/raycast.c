/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/13 20:41:19 by isromero         ###   ########.fr       */
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

void texture_on_img(t_map *map, t_img *img)
{
	int	scale;

	scale = map->line->y * img->line_length
		- (900 * 1.0) * img->line_length
		/ 2 + map->draw->line_height * img->line_length / 2;
	map->line->tex_y = ((scale * img->height) / map->draw->line_height)
		/ img->line_length;
	map->img->addr[map->line->y * map->img->line_length + map->line->x
		* map->img->bits_per_pixel / 8] = img->addr[map->line->tex_y
		* img->line_length + map->line->tex_x * (img->bits_per_pixel / 8)];
	map->img->addr[map->line->y * map->img->line_length + map->line->x
		* (map->img->bits_per_pixel / 8) + 1] = img->addr[map->line->tex_y
		* img->line_length + map->line->tex_x
		* (img->bits_per_pixel / 8) + 1];
	map->img->addr[map->line->y * map->img->line_length + map->line->x
		* (map->img->bits_per_pixel / 8) + 2] = img->addr[map->line->tex_y
		* img->line_length + map->line->tex_x
		* (img->bits_per_pixel / 8) + 2];
}

static void	pixel_on_img(t_map *map, int rgb, int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8] = b;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8 + 1] = g;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8 + 2] = r;
}
void	paint_line(t_map *map, int rgb)
{
	int	y;
	int	y_max;

	if (map->line->y0 < map->line->y1)
	{
		y = map->line->y0;
		y_max = map->line->y1;
	}
	else
	{
		y = map->line->y1;
		y_max = map->line->y0;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			pixel_on_img(map, rgb, map->line->x, y);
			y++;
		}
	}
}

void	draw_texture_image(t_map *map, t_img *img)
{
	int	y_max;

	if (map->line->y0 < map->line->y1)
	{
		map->line->y = map->line->y0;
		y_max = map->line->y1;
	}
	else
	{
		map->line->y = map->line->y1;
		y_max = map->line->y0;
	}
	if (map->line->y >= 0)
	{
		map->line->y--;
		while (++map->line->y < y_max)
			texture_on_img(map, img);
	}
}

void	paint_texture_line(t_map *map, double wall_x)
{
	int	tex_x;
	t_img	*img;

	img = map->no_img;
	if (map->ray->side == EAST)
		img = map->ea_img;
	else if (map->ray->side == NORTH)
		img = map->no_img;
	else if (map->ray->side == WEST)
		img = map->we_img;
	else if (map->ray->side == SOUTH)
		img = map->so_img;
	tex_x = (int)(wall_x * (double)img->width);
	if ((map->ray->side ==  NORTH || map->ray->side == SOUTH) && map->ray->dir_x < 0)
		tex_x = img->width - tex_x - 1;
	else
		tex_x = img->width - tex_x - 1; 
	map->line->y0 = map->draw->draw_start;
	map->line->y1 = map->draw->draw_end;
	map->line->tex_x = tex_x;
	draw_texture_image(map, img);
}

void	draw_textures(t_map *map)
{
	double wall_x;

	wall_x = 0.0;
	if (map->ray->side == NORTH || map->ray->side == SOUTH)
		wall_x = map->player->x + map->ray->perp_wall_dist * map->ray->dir_x;
	else if (map->ray->side == EAST || map->ray->side == WEST)
		wall_x = map->player->y + map->ray->perp_wall_dist * map->ray->dir_y;
	wall_x -= floor(wall_x);
	
	map->line->x = map->ray->col;
	if (map->map[map->ray->map_y][map->ray->map_x] == '1')
		paint_texture_line(map, wall_x);
	
	map->line->y0 = 0;
	map->line->y1 = map->draw->draw_start;
	if((map->cr >= 0 && map->cr <= 255) && (map->cg >= 0 && map->cg <= 255) && (map->cb >= 0 && map->cb <= 255))
		paint_line(map, create_rgb_color(map->cr, map->cg, map->cb));
	else
		paint_line(map, create_rgb_color(0, 0, 255));
	map->line->y0 = 900;
	map->line->y1 = map->draw->draw_end;
	if((map->fr >= 0 && map->fr <= 255) && (map->fg >= 0 && map->fg <= 255) && (map->fb >= 0 && map->fb <= 255))
		paint_line(map, create_rgb_color(map->fr, map->fg, map->fb));
	else
		paint_line(map, create_rgb_color(255, 0, 255));
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
			map->ray->perp_wall_dist = map->ray->side_dist_x - map->ray->delta_dist_x;
		else if (map->ray->side == NORTH || map->ray->side == SOUTH)
			map->ray->perp_wall_dist = map->ray->side_dist_y - map->ray->delta_dist_y;
		/* draw_image(map); */
		
		// Con texturas (haciendo)
		calculate_draw_values(map);
		draw_textures(map);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return 0;
}