/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:54 by isromero          #+#    #+#             */
/*   Updated: 2023/11/08 21:28:59 by isromero         ###   ########.fr       */
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

void	render_ray_2d(t_map *map)
{
	// double initial_angle;

	// initial_angle = map->player->angle - (map->player->angle / 2); // El primer rayo
	
	int		player_x;
	int		player_y;
	double	ray_x;
	double	ray_y;

	player_x = map->player->j_pj * 16 + 8;
	player_y = map->player->i_pj * 16 + 8;
	ray_x = player_x + cos(map->player->angle); // cos suma las x en el eje de coordenadas
	ray_y = player_y + sin(map->player->angle); // sen suma la y en el eje de coordenadas
	while(player_x < map->x * 16 && ray_x < map->x * 16 && ray_y < map->y * 16 && ray_y > 0 && ray_x > 0)
	{
		ray_x = player_x + cos(map->player->angle);
		ray_y = player_y + sin(map->player->angle);
		
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, ray_x, ray_y, 0x0FF0F0);
		player_x = ray_x;
		player_y = ray_y;
	}
}