/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/11/06 17:37:14 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_ray(t_map *map, int j, int i) 
{
    int x_end; 

	x_end = map->x * 20; 
    while (j < x_end) 
	{
		if (map->map[i / 20][j / 20] == '1') 
            break; // Sale del bucle si encuentra una pared
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, j, i, 0xFF0000); // Color rojo (formato RGB)
        j++;
    }
}

void draw_diagonal_line(t_map *map, double angle, int i, int j)
{
    double player_x = j;  // Posición X del jugador
    double player_y = i;  // Posición Y del jugador

    int x_end = map->x * 20;
    
    while (player_x < x_end) {
        // Calcula las coordenadas (x, y) a lo largo de la línea diagonal
        double x = player_x + cos(angle * M_PI / 180.0);
        double y = player_y + sin(angle * M_PI / 180.0);

        int map_x = x / 20; // Convierte la posición X a coordenadas del mapa
        int map_y = y / 20; // Convierte la posición Y a coordenadas del mapa
        if (map->map[map_y][map_x] == '1')
		{
            map->player->len_to_wall = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));
            break;
        }
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0xFF0000); // Color rojo (formato RGB)
        player_x = x;
        player_y = y;
    }
}

void	paint_line(t_map *map, t_line *line, t_ray *ray)
{
	int	y;
	int	y_max;

	if (line->y0 < line->y1)
	{
		y = line->y0;
		y_max = line->y1;
	}
	else
	{
		y = line->y1;
		y_max = line->y0;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			if (ray->side == 0)
				mlx_pixel_put(map->mlx_ptr, map->win_ptr, line->x, y, 0x0000FF);
			else if (ray->side == 1)
				mlx_pixel_put(map->mlx_ptr, map->win_ptr, line->x, y, 0x00FF00);
			y++;
		}
	}
}

int raycast_implementation(t_map *map, t_ray *ray, t_line *line)
{
	int x = 0;
	int w = map->x * 20;
	printf("weiii\n");
	while(x < w)
	{
		ray->hit = 0;
		// Calcular la posición y dirección del rayo
		ray->camera_x = 2 * x / (double)w - 1; // La coordenada en x de la cámara -> camera x es -1 cuando mira 100% izquierda, 0 centro y 1 derecha 100%
		ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		
		// en dónde está el jugador
		ray->map_x = map->player->j_pj;
		ray->map_y = map->player->i_pj;

		if (ray->ray_dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
			ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
		if (ray->ray_dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
			ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
		
		// stepX y stepY En la dirección en la que debe avanzar el rayo en el mundo 2D
		// rayDirX y rayDirY parece lo mismo, pero ellos lo hacen en el mundo3D
		
		// side Indica si el rayo ha impactado en NS(norte-sur)->(1, vertical) o EW(este-oeste)->(0, horitzontal)
	
		// calcular step y sideDist
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
		}

		// ejecutar el algoritmo DDA
		while (ray->hit == 0)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (map->map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}

		// Calculamos la distancia hacia el muro(no euclidiana, es decir, no desde el jugador al muro ya que ahce efecto pez)
		// Dependiendo en dónde impacte el rayo, si NS o EW(dirección de cámara) pues hacemos los cálculos
		if(ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
      	else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

		// Con los cálculos transformamos y convertimos imágenes(las líneas verticales que se van a pintar en pantalla)
		
		if (ray->side == 0) //EW
			line->wall_x = map->player->i_pj + ray->perp_wall_dist * ray->ray_dir_y;
		else
			line->wall_x = map->player->j_pj + ray->perp_wall_dist * ray->ray_dir_x;
		line->wall_x -= floor(line->wall_x);
		
		line->x = x; // ponemos la coordenada de line->x a la coordenada del ancho de pantalla donde estamos recorriendo

		//PINTAMOS
		
		//pintar textura cuando el rayo da a un muro
		line->y0 = 0;
		
		//calculamos altura del muro para saber dónde se empieza a pintar el primer pixel
		double line_height = map->y * 20 / ray->perp_wall_dist;
		line->y1 = (-line_height / 2) + (map->y * 20 / 2); // (draw_start)
		if (line->y1 < 0)
			line->y1 = 0;
		line->y0 = (line_height / 2) + (map->y * 20 / 2); // (draw_end)
		if (line->y0 >= map->y * 20)
			line->y0 = map->y * 20 - 1;
		
		if(ray->hit == 1)
			paint_line(map, line, ray);
		x++;
	}
	return 0;
 }

