/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:54 by isromero          #+#    #+#             */
/*   Updated: 2023/11/12 11:26:24 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_background_2d(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	int		i;
	int		j;

	i = 0;
	j = 0;
	img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
					"assets/fondo.xpm", &width, &height);
	while (j < (map->y * 16))
	{
		i = 0;
		while (i < (map->x * 16))
		{
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, img_ptr, i, j);
			i = i + 16;
		}
		j = j + 16;
	}
	mlx_destroy_image(map->mlx_ptr, img_ptr);
}

void	render_empty_2d(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == ' ')
			{
				img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
						"assets/empty.xpm", &width, &height);
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					img_ptr, j * 16, i * 16);
				mlx_destroy_image(map->mlx_ptr, img_ptr);
			}
			j++;
		}
		i++;
	}
}

void	render_walls_2d(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == '1')
			{
				img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
						"assets/wall.xpm", &width, &height);
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					img_ptr, j * 16, i * 16);
				mlx_destroy_image(map->mlx_ptr, img_ptr);
			}
			j++;
		}
		i++;
	}
}

void	render_char_2d(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == 'E' || map->map[i][j] == 'N' 
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
						"assets/player.xpm", &width, &height);
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					img_ptr, j * 16, i * 16);
				mlx_destroy_image(map->mlx_ptr, img_ptr);
			}
			j++;
		}
		i++;
	}
}
// https://permadi.com/1996/05/ray-casting-tutorial-7/
int find_horizontal_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = tan(angle);

	if ((angle >= M_PI / 2 && angle <= 3 * M_PI / 2)) // El rayo mira hacia arriba
		map->line->line_h.intersection_y = round((ray_y / 16) * (16));
	else if ((angle >= 3 * M_PI / 2 && angle < 2 * M_PI) || (angle >= 0 && angle < M_PI / 2)) // El rayo mira hacia abajo
		map->line->line_h.intersection_y = round((ray_y / 16) * (16));

	if (tan_value != 0)
		map->line->line_h.intersection_x = round((ray_x + (ray_y - map->line->line_h.intersection_y) / tan(angle)));

	int grid_y = map->line->line_h.intersection_y / 16;
	int grid_x = map->line->line_h.intersection_x / 16;

	if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < map->x) 
	{
		if (map->map[grid_y][grid_x] == '1')
			return 1;
	}
	return 0;
}

int find_vertical_intersection(t_map *map, double ray_x, double ray_y, double angle)
{
	double tan_value = tan(angle);

	if ((angle >= 0 && angle < M_PI / 2) || (angle >= 3 * M_PI / 2 && angle < 2 * M_PI)) // El rayo mira hacia la derecha
		map->line->line_v.intersection_x = round((ray_x / 16) * (16));
	else if ((angle >= M_PI / 2 && angle <= 3 * M_PI / 2)) // el rayo mira hacia izquierda
		map->line->line_v.intersection_x = round((ray_x / 16) * (16));

	if (tan_value != 0)
		map->line->line_v.intersection_y = round((ray_y + (ray_x - map->line->line_v.intersection_x) * tan(angle)));

	int grid_y = map->line->line_v.intersection_y / 16;
	int grid_x = map->line->line_v.intersection_x / 16;

	if (grid_y >= 0 && grid_y < map->y && grid_x >= 0 && grid_x < map->x)
	{
		if (map->map[grid_y][grid_x] == '1')
			return 1;
	}
	return 0;
}


void	render_ray_2d(t_map *map, int player_x, int player_y, double angle)
{
	double	ray_x;
	double	ray_y;
	int 	len_to_wall = 0;
	
	map->line->line_h.xa = 16 / tan(angle);
	map->line->line_h.ya = 16;

	map->line->line_v.xa = 16;
	map->line->line_v.ya = 16 / tan(angle);

	if (angle >= M_PI && angle <= (M_PI * 2))
	{
		map->line->line_h.ya *= -1;
		map->line->line_v.ya *= -1;
	}
	if (angle >= M_PI / 2 && angle <= (3 * M_PI / 2))
	{
		map->line->line_h.xa *= -1;
		map->line->line_v.xa *= -1;
	}
	ray_x = player_x + cos(angle) + 8; // cos suma las x en el eje de coordenadas + 8(centro de personaje)
	ray_y = player_y + sin(angle) + 8; // sen suma la y en el eje de coordenadas + 8(centro de personaje)
	while (ray_x >= 0 && ray_x < map->x * 16 && ray_y >= 0 && ray_y < map->y * 16)
	{
        if (find_horizontal_intersection(map, ray_x, ray_y, angle) == 1)
		{
            printf("Hit: (%d, %d)\n", map->line->line_h.intersection_x / 16, map->line->line_h.intersection_y / 16);
			// len_to_wall = ((player_x / 16) -  map->line->intersection_x) / cos(angle);
			// printf("len to wall: %d\n", len_to_wall);
            break;
        }
		else
		{
			map->line->line_h.intersection_x += map->line->line_h.xa;
			map->line->line_h.intersection_y += map->line->line_h.ya;
		}
		if (find_vertical_intersection(map, ray_x, ray_y, angle) == 1)
		{
            printf("Hit: (%d, %d)\n", map->line->line_v.intersection_x / 16, map->line->line_v.intersection_y / 16);
			/* len_to_wall = ((player_x / 16) -  map->line->line_v.intersection_x) / cos(angle);
			printf("len to wall: %d\n", len_to_wall); */
            break;
        }
		else
		{
			map->line->line_v.intersection_x += map->line->line_v.xa;
			map->line->line_v.intersection_y += map->line->line_v.ya;
		}
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, ray_x, ray_y, 0x0FF0F0);
		
		ray_x += cos(angle);
    	ray_y += sin(angle);
	}
}

void	render_all_rays_2d(t_map *map)
{
	double angle;
	render_ray_2d(map, map->player->j_pj * 16, map->player->i_pj * 16, map->player->angle);
	
	angle = map->player->angle - (M_PI / 6); // El primer rayo se dibuja en el ángulo inicial - 30º
	while(angle <= map->player->angle + (M_PI / 6)) // El último rayo se dibuja en el ángulo inicial + 30º
	{
		render_ray_2d(map, map->player->j_pj * 16, map->player->i_pj * 16, angle);
		angle += (60 / map->x) * (M_PI / 180.0);
	}
}
