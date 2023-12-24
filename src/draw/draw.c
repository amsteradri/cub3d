/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:39:39 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 12:41:59 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_map *map)
{
	draw_ceil(map);
	if (map->map[map->ray->map_y][map->ray->map_x] == '1')
		draw_wall(map);
	draw_floor(map);
}

void	draw_ceil(t_map *map)
{
	int	y;

	y = 0;
	while(y < map->draw->draw_start)
	{
		if ((map->cr >= 0 && map->cr <= 255) && (map->cg >= 0 && map->cg <= 255)
		&& (map->cb >= 0 && map->cb <= 255))
			pixel_on_img(map, create_rgb_color(map->cr, map->cg, map->cb), map->line->x, y);
		else
			pixel_on_img(map, create_rgb_color(0, 0, 255), map->line->x, y);
		y++;
	}
}

void	draw_floor(t_map *map)
{
	int	y;

	y = map->draw->draw_end;

	while(y < map->screen_height)
	{
		if ((map->fr >= 0 && map->fr <= 255) && (map->fg >= 0 && map->fg <= 255)
		&& (map->fb >= 0 && map->fb <= 255))
			pixel_on_img(map, create_rgb_color(map->fr, map->fg, map->fb), map->line->x, y);
		else
			pixel_on_img(map, create_rgb_color(255, 0, 255), map->line->x, y);
		y++;
	}
}

void	get_wall_orientation(t_map *map, t_img **img)
{
	if (map->ray->side == EAST)
		*img = map->ea_img;
	else if (map->ray->side == NORTH)
		*img = map->no_img;
	else if (map->ray->side == WEST)
		*img = map->we_img;
	else if (map->ray->side == SOUTH)
		*img = map->so_img;
}

void	draw_wall(t_map *map)
{
	t_img	*img;
	
	img = map->no_img;
	get_wall_orientation(map, &img);
	calculate_wall_x(map);
	calculate_tex_x(map, img);
    map->line->y = map->draw->draw_start;
    while (map->line->y < map->draw->draw_end)
    {
        texture_on_img(map, img);
        map->line->y++;
    }
}
