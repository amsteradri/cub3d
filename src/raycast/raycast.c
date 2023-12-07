/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/07 13:55:59 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->img->addr + (y * map->img->line_length + x * (map->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	draw_image(t_map *map, int x, int projected_slice_height)
// {
// 	int color_sky = 0xABCDEF;

// 	if (map->img->bits_per_pixel != 32)
// 		color_sky = mlx_get_color_value(map->mlx_ptr, color_sky);

// 	int color_wall = 0x00AA0000;

// 	if (map->img->bits_per_pixel != 32)
// 		color_wall = mlx_get_color_value(map->mlx_ptr, color_wall);

// 	int color_floor = 0x00FF00;

// 	if (map->img->bits_per_pixel != 32)
// 		color_floor = mlx_get_color_value(map->mlx_ptr, color_floor);
// 	int ceiling_height = (map->screen_height - projected_slice_height) / 2;
// 	int floor_height = map->screen_height - ceiling_height;
	
// 	for (int y = 0; y < ceiling_height; y++)
// 	{
// 		int pixel = (y * map->img->line_length) + (x * 4);
		

// 		if (map->img->endian == 1)
// 		{
// 			map->img->addr[pixel + 0] = (color_sky >> 24);
// 			map->img->addr[pixel + 1] = (color_sky >> 16) & 0xFF;
// 			map->img->addr[pixel + 2] = (color_sky >> 8) & 0xFF;
// 			map->img->addr[pixel + 3] = (color_sky) & 0xFF;
// 		}
// 		else if (map->img->endian == 0)
// 		{
// 			map->img->addr[pixel + 0] = (color_sky) & 0xFF;
// 			map->img->addr[pixel + 1] = (color_sky >> 8) & 0xFF;
// 			map->img->addr[pixel + 2] = (color_sky >> 16) & 0xFF;
// 			map->img->addr[pixel + 3] = (color_sky >> 24);
// 		}
// 	}

// 	for (int y = ceiling_height; y < floor_height; y++)
// 	{
// 		int pixel = (y * map->img->line_length) + (x * 4);
		
// 		if (map->img->endian == 1)
// 		{
// 			map->img->addr[pixel + 0] = (color_wall >> 24);
// 			map->img->addr[pixel + 1] = (color_wall >> 16) & 0xFF;
// 			map->img->addr[pixel + 2] = (color_wall >> 8) & 0xFF;
// 			map->img->addr[pixel + 3] = (color_wall) & 0xFF;
// 		}
// 		else if (map->img->endian == 0)
// 		{
// 			map->img->addr[pixel + 0] = (color_wall) & 0xFF;
// 			map->img->addr[pixel + 1] = (color_wall >> 8) & 0xFF;
// 			map->img->addr[pixel + 2] = (color_wall >> 16) & 0xFF;
// 			map->img->addr[pixel + 3] = (color_wall >> 24);
// 		}
// 	}

// 	for (int y = floor_height; y < map->screen_height; y++)
// 	{
// 		int pixel = (y * map->img->line_length) + (x * 4);
		
// 		if (map->img->endian == 1)
// 		{
// 			map->img->addr[pixel + 0] = (color_floor >> 24);
// 			map->img->addr[pixel + 1] = (color_floor >> 16) & 0xFF;
// 			map->img->addr[pixel + 2] = (color_floor >> 8) & 0xFF;
// 			map->img->addr[pixel + 3] = (color_floor) & 0xFF;
// 		}
// 		else if (map->img->endian == 0)
// 		{
// 			map->img->addr[pixel + 0] = (color_floor) & 0xFF;
// 			map->img->addr[pixel + 1] = (color_floor >> 8) & 0xFF;
// 			map->img->addr[pixel + 2] = (color_floor >> 16) & 0xFF;
// 			map->img->addr[pixel + 3] = (color_floor >> 24);
// 		}
// 	}
// }

int find_vertical_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = (tan(angle));
	double face = ray_x + (100.0 * cos(angle));
	int grid_y = 0;
	int grid_x = 0;
	map->line->line_v.intersection_x = 0;
	map->line->line_v.intersection_y = 0;

	if (face <= ray_x) // El rayo mira hacia la derecha
	{
		map->line->line_v.intersection_x = floor(ray_x / 64) * (64) - 1;
		map->line->line_v.xa = -64;
		map->line->line_v.ya = (64 * tan_value) * -1;
	}
	else// el rayo mira hacia izquierda
	{
		map->line->line_v.intersection_x = floor(ray_x / 64) * (64) + 64;
		map->line->line_v.xa = 64;
		map->line->line_v.ya = 64 * tan_value;
	}
	/* if (tan_value != 0 && angle !=  4.712389) */
		map->line->line_v.intersection_y = ray_y - (ray_x - map->line->line_v.intersection_x) * tan_value;
	/* else
		return 0; */
	int i = -1;
	while (++i <= map->x)
	{
		grid_y = floor(map->line->line_v.intersection_y) / 64;
		grid_x = floor(map->line->line_v.intersection_x) / 64;

		if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < (int)ft_strlen(map->map[grid_y]))
		{
			if (map->map[grid_y][grid_x] == '1')
			{
				map->line->line_v.perp_dist = fabs(sqrt(pow(ray_x - map->line->line_v.intersection_x, 2) + pow(ray_y - map->line->line_v.intersection_y, 2)));
				// Para el fish eye
				//map->line->line_v.correct_dist = map->line->line_v.perp_dist * cos(angle); 
				return 1;
			}
		}
		// Actualizar coordenadas solo si no hay colisión
		map->line->line_v.intersection_x += map->line->line_v.xa;
		map->line->line_v.intersection_y += map->line->line_v.ya;
	
    }
	return 0; // Nunca debería llegar aquí, ya que la función siempre debería salir con una colisión
}



//SE VE MAS O MENOS IGUL CON EL FABS EN LA SQRT , NO SE SI DEJARLO

int find_horizontal_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = (tan(angle));
	double face = ray_y + (100 * sin(angle));
	//printf("path textura: %s\n", map->no);
	int grid_y = 0;
	int grid_x = 0;
	map->line->line_h.intersection_y = 0;
	map->line->line_h.intersection_x = 0;
	if (face <= ray_y) // El rayo mira hacia arriba
	{	
		map->line->line_h.intersection_y = floor(ray_y / 64) * (64) - 1;
		map->line->line_h.ya = -64;
		map->line->line_h.xa = (64 / tan_value) * -1;
	}
	else// El rayo mira hacia abajo
	{
		map->line->line_h.intersection_y = floor(ray_y / 64) * (64) + 64;
		map->line->line_h.ya = 64;
		map->line->line_h.xa = 64 / tan_value;
	}
	/* if (tan_value != 0 && angle !=  4.712389) */
		map->line->line_h.intersection_x = ray_x - (ray_y - map->line->line_h.intersection_y) / tan_value;
	/* else
		return 0; */
	
	int i = -1;
	while (++i <= map->y)
	{
		grid_y = floor(map->line->line_h.intersection_y) / 64;
		grid_x = floor(map->line->line_h.intersection_x) / 64;
		if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < (int)ft_strlen(map->map[grid_y]))
		{
			if (map->map[grid_y][grid_x] == '1')
			{
				map->line->line_h.perp_dist = fabs(sqrt(pow(ray_x - map->line->line_h.intersection_x, 2) + pow(ray_y - map->line->line_h.intersection_y, 2)));
				// Para el fish eye
				//map->line->line_h.correct_dist = map->line->line_h.perp_dist * cos(angle);
				return 1;
			}
		}
		// Actualizar coordenadas solo si no hay colisión
		map->line->line_h.intersection_x += map->line->line_h.xa;
		map->line->line_h.intersection_y += map->line->line_h.ya;
    }
	return 0;
}

int	raycast(t_map *map)
{
	int		projected_slice_height;
	double 	angle;
	double 	initial_angle;
	/* int	texture_offset_x;
	int	texture_offset_y;
	int	texture_color;
	int	distance_from_top; */
	
	map->ray->current_col = -1;
	projected_slice_height = 0;
	initial_angle = map->ray->angle - (30.0 * M_PI / 180.0);
	angle = initial_angle;
	if (angle < 0.0 && angle >= -M_PI * 2.0)
		angle += M_PI * 2.0;
	
	while(++map->ray->current_col < map->screen_width)
	{
		find_horizontal_intersection(map, (map->player->x) * 64.0, (map->player->y) * 64.0, angle);
		find_vertical_intersection(map, (map->player->x) * 64.0, (map->player->y) * 64.0, angle);
		if (map->line->line_h.perp_dist <= map->line->line_v.perp_dist)
		{
			projected_slice_height = floor((64.0 / map->line->line_h.perp_dist) * map->ray->dist_player_projection_plane);
			map->ray->side = 1;
		}
			
		else if (map->line->line_h.perp_dist > map->line->line_v.perp_dist)
		{
			projected_slice_height = floor((64.0 / map->line->line_v.perp_dist) * map->ray->dist_player_projection_plane);
			map->ray->side = 0;
		}
		
		///////////// TEXTURAS ////////////////////
		/* if (map->ray->side == 1)
		{
			texture_offset_x = (int)((map->line->line_h.perp_dist / 64.0) * 64) % 64;
		}
		else if (map->ray->side == 0)
		{
			texture_offset_x = (int)((map->line->line_v.perp_dist / 64.0) * 64) % 64;
		} */
		/////////////////////////////////////////
		
        if (projected_slice_height > map->screen_height)
            projected_slice_height = map->screen_height;
		draw_image_with_textures(map, map->ray->current_col, projected_slice_height);
		angle += map->ray->angle_between_rays;
		
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img->img, 0, 0);
	
	return 0;
}