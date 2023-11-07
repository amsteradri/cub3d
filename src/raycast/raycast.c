/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:57:02 by isromero          #+#    #+#             */
/*   Updated: 2023/11/07 18:42:25 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void draw_ray(t_map *map, int j, int i) 
{
    int x_end; 

	x_end = map->x * 20;
    while (j < x_end) 
	{
		if (map->map[i / 20][j / 20] == '1') 
            break; // Sale del bucle si encuentra una pared
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, j, i, 0x00FF00); // Color rojo (formato RGB)
        j++;
    }
}

void draw_diagonal_ray(t_map *map, double angle, int i, int j)
{
    double player_x = j;  // Posición X del jugador
    double player_y = i;  // Posición Y del jugador

    int x_end = map->x * 20;
	while (player_x < x_end)
	{
		// Calcula las coordenadas (x, y) a lo largo de la línea diagonal
		double x = player_x + cos(angle);
		double y = player_y + sin(angle);

		int map_x = x / 20; // Convierte la posición X a coordenadas del mapa
		int map_y = y / 20; // Convierte la posición Y a coordenadas del mapa
		if (map->map[map_y][map_x] == '1')
		{
			map->player->len_to_wall = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));
			break;
		}
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0xFF0000);
		player_x = x;
		player_y = y;
	}
}


