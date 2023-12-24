/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:13:08 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 17:17:12 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars_line(t_map *map)
{
	map->line = (t_line *)malloc(sizeof(t_line));
	map->line->x = 0;
	map->line->y = 0;
	map->line->tex_x = 0;
	map->line->tex_y = 0;
}

void	init_vars_texture(t_map *map)
{
	map->texture = (t_img *)malloc(sizeof(t_img));
	map->texture->img = NULL;
	map->texture->addr = NULL;
	map->texture->bits_per_pixel = 0;
	map->texture->line_length = 0;
	map->texture->endian = 0;
	map->texture->height = 0;
	map->texture->width = 0;
}

void	inits_structs(t_map *map)
{
	init_vars_map(map);
	init_vars_imgs(map);
	init_vars_draw(map);
	init_vars_ray(map);
	init_vars_player(map);
	init_vars_line(map);
	init_vars_texture(map);
}
