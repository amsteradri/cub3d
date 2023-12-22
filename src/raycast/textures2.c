/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:38:40 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/22 20:59:45 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pixel_on_img(t_map *map, int rgb, int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel
		/ 8] = b;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8
		+ 1] = g;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8
		+ 2] = r;
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
	int		tex_x;
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
	if ((map->ray->side == NORTH || map->ray->side == SOUTH)
		&& map->ray->dir_x < 0)
	{
		tex_x = img->width - tex_x - 1;
		if (tex_x < 0)
			tex_x = 0;
		else if (tex_x >= img->width)
			tex_x = img->width - 1;
	}
	else
	{
		tex_x = img->width - tex_x - 1;
		if (tex_x < 0)
			tex_x = 0;
		else if (tex_x >= img->width)
			tex_x = img->width - 1;
	}
	map->line->y0 = map->draw->draw_start;
	map->line->y1 = map->draw->draw_end;
	map->line->tex_x = tex_x;
	draw_texture_image(map, img);
}

void	draw_textures(t_map *map)
{
	double	wall_x;

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
	if ((map->cr >= 0 && map->cr <= 255) && (map->cg >= 0 && map->cg <= 255)
		&& (map->cb >= 0 && map->cb <= 255))
		paint_line(map, create_rgb_color(map->cr, map->cg, map->cb));
	else
		paint_line(map, create_rgb_color(0, 0, 255));
	map->line->y0 = 900;
	map->line->y1 = map->draw->draw_end;
	if ((map->fr >= 0 && map->fr <= 255) && (map->fg >= 0 && map->fg <= 255)
		&& (map->fb >= 0 && map->fb <= 255))
		paint_line(map, create_rgb_color(map->fr, map->fg, map->fb));
	else
		paint_line(map, create_rgb_color(255, 0, 255));
}
