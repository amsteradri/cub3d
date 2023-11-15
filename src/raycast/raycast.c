/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/11/15 08:42:57 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int find_vertical_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = tan(angle);

	if ((angle >= 0.0 && angle < M_PI / 2) || (angle >= 3 * M_PI / 2 && angle <= 2 * M_PI)) // El rayo mira hacia la derecha
	{
		map->line->line_v.intersection_x = floor(ray_x / 16) * (16) + 16;
		map->line->line_v.xa = 16;
	}
		
	else if ((angle >= M_PI / 2 && angle <= 3 * M_PI / 2)) // el rayo mira hacia izquierda
	{
		map->line->line_v.intersection_x = floor(ray_x / 16) * (16) - 1;
		map->line->line_v.xa = -16;
	}
	
	if (tan_value != 0)
			map->line->line_v.intersection_y = ray_y + (ray_x - map->line->line_v.intersection_x) * tan(angle);
	else
		return 0;

	map->line->line_v.ya = 16 / tan(angle);

	while (1)
	{
		int grid_y = map->line->line_v.intersection_y / 16;
		int grid_x = map->line->line_v.intersection_x / 16;

		if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < map->x)
		{
			if (map->map[grid_y][grid_x] == '1')
			{
				map->line->line_v.xa = 0;
				map->line->line_v.ya = 0;
				return 1;
			}
		}

		// Actualizar coordenadas solo si no hay colisión
		map->line->line_v.intersection_x += map->line->line_v.xa;
		map->line->line_v.intersection_y += map->line->line_v.ya;
    }
	return 0; // Nunca debería llegar aquí, ya que la función siempre debería salir con una colisión
}

int find_horizontal_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = tan(angle);

	if (angle > M_PI / 2 && angle < 3 * M_PI / 2) // El rayo mira hacia arriba
	{
		map->line->line_h.intersection_y = floor(ray_y / 16) * (16) - 1;
		map->line->line_h.ya = -16;
	}

	else if (angle >= 0.0 && angle < M_PI / 2) // El rayo mira hacia abajo
	{
		map->line->line_h.intersection_y = floor(ray_y / 16) * (16) + 16;
		map->line->line_h.ya = 16;
	}

	if (tan_value != 0)
			map->line->line_h.intersection_x = ray_x + (ray_y - map->line->line_h.intersection_y) / tan(angle);
	else
		return 0;

	map->line->line_h.xa = 16 / tan(angle);

	while (1)
	{
		int grid_y = map->line->line_h.intersection_y / 16;
		int grid_x = map->line->line_h.intersection_x / 16;

		if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < map->x)
		{
			if (map->map[grid_y][grid_x] == '1')
			{
				map->line->line_h.xa = 0;
				map->line->line_h.ya = 0;
				return 1;
			}
		}

		// Actualizar coordenadas solo si no hay colisión
		map->line->line_h.intersection_x += map->line->line_h.xa;
		map->line->line_h.intersection_y += map->line->line_h.ya;
    }
	return 0; // Nunca debería llegar aquí, ya que la función siempre debería salir con una colisión
}

void	raycast(t_map *map)
{
	map->ray->current_col = 0;
	
	// Queremos lanzar el nº de rayos que tenga el ancho de pantalla
	while(map->ray->current_col < (map->x * 16))
	{
		// Entre rayo y rayo sabiendo que nuestro fov es 60 calculamos el ángulo de cada rayo sabiendo al distancia que hay entre ellos
		map->ray->angle = map->ray->angle_between_rays * map->ray->current_col;
		find_horizontal_intersection(map, map->player->x * 16, map->player->y * 16, map->ray->angle);
		find_vertical_intersection(map, map->player->x * 16, map->player->y * 16, map->ray->angle);
		map->ray->current_col++;
	}
}


