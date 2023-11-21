/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/11/21 08:56:22 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->img->addr + (y * map->img->line_length + x * (map->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/* void	draw_slice(t_map *map, int x, int projected_slice_height)
{
	int ceiling_height = (map->screen_height - projected_slice_height) / 2;
    int floor_height = map->screen_height - ceiling_height;

    // Dibuja el techo
    for (int y = 0; y < ceiling_height; y++)
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0x003333);

    // Dibuja el muro
    for (int y = ceiling_height; y < floor_height; y++)
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0x00FFFFFF);

    // Dibuja el suelo
    for (int y = floor_height; y < map->screen_height; y++)
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0x00FF00);
} */

void	draw_image(t_map *map, int x, int projected_slice_height)
{
	int color_sky = 0xABCDEF;
	
	if (map->img->bits_per_pixel != 32)
		color_sky = mlx_get_color_value(map->mlx_ptr, color_sky);
	
	int color_wall = 0x00FFFFFF;
	
	if (map->img->bits_per_pixel != 32)
		color_wall = mlx_get_color_value(map->mlx_ptr, color_wall);

	int color_floor = 0x00FF00;
	
	if (map->img->bits_per_pixel != 32)
		color_floor = mlx_get_color_value(map->mlx_ptr, color_floor);
	
	int ceiling_height = (map->screen_height - projected_slice_height) / 2;
    int floor_height = map->screen_height - ceiling_height;
	
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

int find_vertical_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = tan(angle);

	if (angle >= (3 * M_PI / 2) && angle < (M_PI / 2)) // El rayo mira hacia la derecha
	{
		map->line->line_v.intersection_x = floor(ray_x / 16) * (16) + 16;
		map->line->line_v.xa = 16;
	}
	else if (angle >= (M_PI / 2) && angle < (3 * M_PI / 2)) // el rayo mira hacia izquierda
	{
		map->line->line_v.intersection_x = floor(ray_x / 16) * (16) - 1;
		map->line->line_v.xa = -16;
	}
	
	if (tan_value != 0)
			map->line->line_v.intersection_y = ray_y + (ray_x - map->line->line_v.intersection_x) * tan(angle);
	else
		return 0;

	map->line->line_v.ya = 16.0 * tan(angle);

	int i = 0;
	while (i <= map->x)
	{
		int grid_y = map->line->line_v.intersection_y / 16;
		int grid_x = map->line->line_v.intersection_x / 16;

		if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < map->x)
		{
			if (map->map[grid_y][grid_x] == '1')
			{
				// no pitágoras por rendimiento pero así perdemos un poco de precisión
				// para mejorar precisión calculamos una intersección distinta para la distancia dependiendo de la dirección del rayo
				/* if (angle >= (3 * M_PI / 2) && angle < (M_PI / 2))
					map->line->line_v.perp_dist = fabs(ray_x - map->line->line_v.intersection_x) / cos(angle);
				else */
				map->line->line_v.perp_dist = fabs(ray_y - map->line->line_v.intersection_y) / sin(angle);
				// Para el fish eye
				map->line->line_v.correct_dist = map->line->line_v.perp_dist * cos(angle);
				return 1;
			}
		}
		// Actualizar coordenadas solo si no hay colisión
		map->line->line_v.intersection_x += map->line->line_v.xa;
		map->line->line_v.intersection_y += map->line->line_v.ya;
		i++;
    }
	return 0; // Nunca debería llegar aquí, ya que la función siempre debería salir con una colisión
}

int find_horizontal_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = tan(angle);

	if (angle >= 0 && angle < M_PI) // El rayo mira hacia arriba
	{
		map->line->line_h.intersection_y = floor(ray_y / 16) * (16) - 1;
		map->line->line_h.ya = -16;
	}

	else if (angle >= M_PI && angle < (M_PI * 2)) // El rayo mira hacia abajo
	{
		map->line->line_h.intersection_y = floor(ray_y / 16) * (16) + 16;
		map->line->line_h.ya = 16;
	}

	if (tan_value != 0)
			map->line->line_h.intersection_x = ray_x + (ray_y - map->line->line_h.intersection_y) / tan(angle);
	else
		return 0;

	map->line->line_h.xa = 16.0 / tan(angle);

	int i = 0;
	while (i <= map->y)
	{
		int grid_y = map->line->line_h.intersection_y / 16;
		int grid_x = map->line->line_h.intersection_x / 16;

		if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < map->x)
		{
			if (map->map[grid_y][grid_x] == '1')
			{
				// no pitágoras por rendimiento pero así perdemos un poco de precisión
				// para mejorar precisión calculamos una intersección distinta para la distancia dependiendo de la dirección del rayo
				/* if (angle >= 0 && angle < M_PI)
					map->line->line_h.perp_dist = fabs(ray_y - map->line->line_h.intersection_y) / sin(angle);
				else */
				map->line->line_h.perp_dist = fabs(ray_x - map->line->line_h.intersection_x) / cos(angle);
				// Para el fish eye
				map->line->line_h.correct_dist = map->line->line_h.perp_dist * cos(angle);
				return 1;
			}
		}
		// Actualizar coordenadas solo si no hay colisión
		map->line->line_h.intersection_x += map->line->line_h.xa;
		map->line->line_h.intersection_y += map->line->line_h.ya;
		i++;
    }
	return 0; // Nunca debería llegar aquí, ya que la función siempre debería salir con una colisión
}

int	raycast(t_map *map)
{
	int	projected_slice_height;
	double angle;
	double initial_angle;
	
	map->ray->current_col = 0;
	projected_slice_height = 0;
	initial_angle = map->ray->angle - (30 * M_PI / 180.0);
	angle = initial_angle;
	// Queremos lanzar el nº de rayos que tenga el ancho de pantalla
	while(map->ray->current_col < map->screen_width)
	{
		find_horizontal_intersection(map, map->player->x * 16, map->player->y * 16, angle);
		find_vertical_intersection(map, map->player->x * 16, map->player->y * 16, angle);
		if (map->line->line_h.correct_dist <= map->line->line_v.correct_dist && map->line->line_h.correct_dist != 0 && map->line->line_v.correct_dist != 0)
			projected_slice_height = ceil((16 / map->line->line_h.correct_dist) * map->ray->dist_player_projection_plane);
		else if (map->line->line_h.correct_dist > map->line->line_v.correct_dist && map->line->line_v.correct_dist != 0 && map->line->line_h.correct_dist != 0)
			projected_slice_height = ceil((16 / map->line->line_v.correct_dist) * map->ray->dist_player_projection_plane);
		draw_image(map, map->ray->current_col, projected_slice_height);
		angle += map->ray->angle_between_rays;
		map->ray->current_col++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	return 0;
}


// PROBLEMA DE MOVIMIENTOS??? HORIZONTAL AND VERTICAL MOTIONS???