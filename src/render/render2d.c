/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:54 by isromero          #+#    #+#             */
/*   Updated: 2023/12/18 20:10:51 by adgutier         ###   ########.fr       */
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
	mlx_destroy_image(map->mlx_ptr, map->wall_2d->img);
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
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->char_2d->img, j
					* 4, i * 4);
			j++;
		}
		i++;
	}
	mlx_destroy_image(map->mlx_ptr, map->char_2d->img);
}
