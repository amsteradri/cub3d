/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:43 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 17:16:15 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls_2d(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->wall_2d->img, j * 4 + 30, i * 4 + 30);
			j++;
		}
		i++;
	}
}

void	draw_diagonal_line(t_map *map, double x, double y)
{
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;

	dir_x = map->player->dir_x + map->player->plane_x
		* map->ray->offset / map->ray->fov;
	dir_y = map->player->dir_y + map->player->plane_y
		* map->ray->offset / map->ray->fov;
	while (1)
	{
		x += dir_x * 0.03;
		y += dir_y * 0.03;
		map_x = (int)(x / 4);
		map_y = (int)(y / 4);
		if (map_x < 0 || map_y < 0 || map_y >= map->y
			|| map_x >= (int)ft_strlen(map->map[map_y]))
			break ;
		if (map->map[map_y][map_x] == '1')
			break ;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr,
			(int)x + 30, (int)y + 30, 0xFFFFFF);
	}
}

void	render_char_2d(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == 'E' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->char_2d->img, j * 4 + 30, i * 4 + 30);
				map->ray->offset = -map->ray->fov / 2;
				while (map->ray->offset <= map->ray->fov / 2)
				{
					draw_diagonal_line(map, j * 4 + 2, i * 4 + 2);
					map->ray->offset += map->ray->step;
				}
			}
			j++;
		}
		i++;
	}
}

int	render_all(t_map *map)
{
	raycast(map);
	render_walls_2d(map);
	render_char_2d(map);
	return (0);
}
