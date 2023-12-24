/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:41:28 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 13:51:42 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_draw_values(t_map *map)
{
	map->draw->line_height = (int)(map->screen_height
			/ map->ray->perp_wall_dist);
	map->draw->draw_start = -map->draw->line_height / 2 + map->screen_height
		/ 2;
	if (map->draw->draw_start < 0)
		map->draw->draw_start = 0;
	map->draw->draw_end = map->draw->line_height / 2 + map->screen_height / 2;
	if (map->draw->draw_end >= map->screen_height)
		map->draw->draw_end = map->screen_height - 1;
}

void	calculate_tex_x(t_map *map, t_img *img)
{
	map->line->tex_x = (int)(map->ray->wall_x * (double)img->width);
	if ((map->ray->side == NORTH || map->ray->side == SOUTH)
		&& map->ray->dir_x < 0)
	{
		map->line->tex_x = img->width - map->line->tex_x - 1;
		if (map->line->tex_x < 0)
			map->line->tex_x = 0;
		else if (map->line->tex_x >= img->width)
			map->line->tex_x = img->width - 1;
	}
	else
	{
		map->line->tex_x = img->width - map->line->tex_x - 1;
		if (map->line->tex_x < 0)
			map->line->tex_x = 0;
		else if (map->line->tex_x >= img->width)
			map->line->tex_x = img->width - 1;
	}
}

void	calculate_wall_x(t_map *map)
{
	if (map->ray->side == NORTH || map->ray->side == SOUTH)
		map->ray->wall_x = map->player->x + map->ray->perp_wall_dist
			* map->ray->dir_x;
	else if (map->ray->side == EAST || map->ray->side == WEST)
		map->ray->wall_x = map->player->y + map->ray->perp_wall_dist
			* map->ray->dir_y;
	map->ray->wall_x -= floor(map->ray->wall_x);
	map->line->x = map->ray->col;
}
