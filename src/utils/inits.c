/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:12:13 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 17:51:15 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars_map(t_map *map)
{
	map->y = map_height(map->map);
	map->x = find_longest_line_length(map->map);
	map->screen_width = 1600;
	map->screen_height = 900;
	map->mlx_ptr = NULL;
	map->win_ptr = NULL;
}

void	init_vars_imgs(t_map *map)
{
	map->img = (t_img *)malloc(sizeof(t_img));
	map->img->img = NULL;
	map->img->addr = NULL;
	map->img->bits_per_pixel = 0;
	map->img->line_length = 0;
	map->img->endian = 0;
	map->img->height = 0;
	map->img->width = 0;
	map->no_img = (t_img *)malloc(sizeof(t_img));
	map->we_img = (t_img *)malloc(sizeof(t_img));
	map->ea_img = (t_img *)malloc(sizeof(t_img));
	map->so_img = (t_img *)malloc(sizeof(t_img));
	map->char_2d = (t_img *)malloc(sizeof(t_img));
	map->wall_2d = (t_img *)malloc(sizeof(t_img));
	map->back_2d = (t_img *)malloc(sizeof(t_img));
}

void	init_vars_draw(t_map *map)
{
	map->draw = (t_draw *)malloc(sizeof(t_draw));
	map->draw->line_height = 0;
	map->draw->draw_start = 0;
	map->draw->draw_end = 0;
}

void	init_vars_ray(t_map *map)
{
	map->ray = (t_ray *)malloc(sizeof(t_ray));
	map->ray->side = 0;
	map->ray->dir_x = 0.0;
	map->ray->dir_y = 0.0;
	map->ray->delta_dist_x = 0.0;
	map->ray->delta_dist_y = 0.0;
	map->ray->side_dist_x = 0.0;
	map->ray->side_dist_y = 0.0;
	map->ray->perp_wall_dist = 0.0;
	map->ray->step_x = 0;
	map->ray->step_y = 0;
	map->ray->map_x = 0;
	map->ray->map_y = 0;
	map->ray->wall_x = 0.0;
	map->ray->col = 0;
	map->ray->fov = 66.0;
	map->ray->step = 20.0;
	map->ray->offset = -map->ray->fov / 2;
}

void	init_vars_player(t_map *map)
{
	map->player = (t_player *)malloc(sizeof(t_player));
	map->player->y = 0.0;
	map->player->x = 0.0;
	map->player->dir_x = 0.0;
	map->player->dir_y = 0.0;
	map->player->plane_x = 0.0;
	map->player->plane_y = 0.0;
}
