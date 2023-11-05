/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/11/05 18:16:30 by isromero         ###   ########.fr       */
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

void raycast_implementation(t_map *map)
{
	double posX = map->player->j_pj;
	double posY = map->player->i_pj;
	double dirX = map->player->vect_x;
	double dirY = map->player->vect_y;
	double planeX = 0;
	double planeY = 0.66;
	
	int x = 0;
	int w = map->x * 20;
	while(x < w)
	{
		// Calcular la posición y dirección del rayo
		double cameraX = 2 * x / (double)w - 1; // La coordenada en x de la cámara -> camera x es -1 cuando mira 100% izquierda, 0 centro y 1 derecha 100%
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		// Cálculo de otras distancias(explicación de variables)
		
		// sideDistX y sideDistY son las distancias iniciales que el rayo tiene que recorrer desde su posición del jugador hasta
		// llegar al primer borde (lado) en X e Y. Son esenciales para ver cuánto ha avanzado el rayo antes de cruzar un borde y cambiar de casilla en el mapa
		// Resumen: es la distancia recorrida dentro del bloque, va cambiando según se va moviendo de bloque en bloque
		
		// deltaDistX y deltaDistY realmente representa las distancias que el rayo tiene que recorrer para pasar de un lado a otro

		// Resumen total: la diferencia entre estas distancias es que una es la distancia ya recorrida dentro de un bloque y la otra la faltante para llegar a x bloque
		
		// en dónde está el jugador
		int mapX = map->player->j_pj;
		int mapY = map->player->i_pj;

		double sideDistX;
		double sideDistY;
		
		double	deltaDistX;
		double	deltaDistY;

		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1.0 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1.0 / rayDirY);

		double	perpWallDist; // Longitud del rayo desde el jugador hasta que impacta
		
		// En la dirección en la que debe avanzar el rayo en el mundo 2D
		// rayDirX y rayDirY parece lo mismo, pero ellos lo hacen en el mundo3D
		double stepX;
		double stepY;
		
		// Indica si el rayo ha impactado en NS(norte-sur)->(1, vertical) o EW(este-oeste)->(0, horitzontal)
		double side;
		int hit = 0;

		// calcular step y sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		// ejecutar el algoritmo DDA
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map->map[mapX][mapY] == '1')
				hit = 1;
		}

		// Calculamos la distancia hacia el muro(no euclidiana, es decir, no desde el jugador al muro ya que ahce efecto pez)
		// Dependiendo en dónde impacte el rayo, si NS o EW(dirección de cámara) pues hacemos los cálculos
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
      	else
			perpWallDist = (sideDistY - deltaDistY);
	}
 }