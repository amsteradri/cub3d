/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:54 by isromero          #+#    #+#             */
/*   Updated: 2023/12/18 22:00:22 by isromero         ###   ########.fr       */
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

void	draw_diagonal_line(t_map *map, double dir_x, double dir_y, double x, double y)
{
    int x_end = map->x * 4;
	int map_x;
	int map_y;

    while ((int)x < x_end) 
	{
        x += dir_x * 0.1; // El 0.1 es para que checkee varias veces el rayo antes de chocar, así no traspasan los rayos
        y += dir_y * 0.1;
        map_x = (int)(x / 4);
        map_y = (int)(y / 4);
        if (map->map[map_y][map_x] == '1')
            break;
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, (int)x, (int)y, 0xFFFFFF);
    }
}

void	render_char_2d(t_map *map)
{
	int i;
	int j;
	double fov;
	double step;
	double offset;
	
	i = 0;
	fov = 66;
	while (i < map->y) 
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i])) 
		{
			if (map->map[i][j] == 'E' || map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W') 
			{
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->char_2d->img, j * 4, i * 4);
				step = fov / 66;
				offset = -fov / 2;
				while (offset <= fov / 2)
				{
					draw_diagonal_line(map, map->player->dir_x + map->player->plane_x * offset / fov, map->player->dir_y + map->player->plane_y * offset / fov, j * 4 + 2, i * 4 + 2);
					offset += step;
				}
			}
			j++;
		}
		i++;
	}
}

