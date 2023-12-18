/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:54 by isromero          #+#    #+#             */
/*   Updated: 2023/12/18 20:45:45 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls_2d(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->y - 1)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]) - 1)
		{
			
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->wall_2d->img, j
					* 4, i * 4);	
			
			j++;
		}
		i++;
	}
	// mlx_destroy_image(map->mlx_ptr, map->wall_2d->img);
}

void	render_back_2d(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->y - 1)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]) - 1)
		{
			
			if (map->map[i][j] == '0')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->back_2d->img, j
					* 4, i * 4);	
			
			j++;
		}
		i++;
	}
	// mlx_destroy_image(map->mlx_ptr, map->wall_2d->img);
}

void draw_ray(t_map *map, int j, int i) 
{
    int x_end; 

	x_end = map->x * 4; 
    while (j < x_end) 
	{
		if (map->map[i / 4][j / 4] == '1') 
		{
            break; // Sale del bucle si encuentra una pared
        }
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, j, i, 0x000000); // Color rojo (formato RGB)
        j++;
    }
}

void draw_diagonal_line(t_map *map, double angle, int i, int j) 
{
    double player_x = j;  // Posición X del jugador
    double player_y = i;  // Posición Y del jugador

    int x_end = map->x * 4;

    while (player_x < x_end) {
        // Calcula las coordenadas (x, y) a lo largo de la línea diagonal
        double x = player_x + cos(angle * M_PI / 180.0);
        double y = player_y + sin(angle * M_PI / 180.0);

        int map_x = x / 4; // Convierte la posición X a coordenadas del mapa
        int map_y = y / 4; // Convierte la posición Y a coordenadas del mapa

        if (map->map[map_y][map_x] == '1') {
            map->player->len_to_wall = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));
            break;
        }

        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0x000000); // Color rojo (formato RGB)
        player_x = x;
        player_y = y;
    }
}

void	render_char_2d(t_map *map)
{
	int		i;
	int		j;
	int		angle = 50;


	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			
			if (map->map[i][j] == 'E' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->char_2d->img, j
					* 4, i * 4);
				draw_ray(map, j * 4 + 2, i * 4 + 2);
				draw_diagonal_line(map, 50, i * 4 , j * 4);
				while(angle > -50)
				{
					draw_diagonal_line(map, angle, i * 4 , j * 4 + 4);
					angle--;
				}
				draw_diagonal_line(map, -50, i * 4, j * 4 + 4);
			}
			j++;
		}
		i++;
	}
	// mlx_destroy_image(map->mlx_ptr, map->char_2d->img);
}
