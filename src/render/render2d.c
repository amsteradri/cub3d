/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:54 by isromero          #+#    #+#             */
/*   Updated: 2023/12/16 16:53:14 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls_2d(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	int		i;
	int		j;

	i = 0;
	j = 0;
	img_ptr = mlx_xpm_file_to_image(map->mlx_ptr, "assets/wall.xpm",
						&width, &height);
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, img_ptr, j
					* 4, i * 4);
			j++;
		}
		i++;
	}
	mlx_destroy_image(map->mlx_ptr, img_ptr);
}

void	render_char_2d(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	int		i;
	int		j;

	i = 0;
	img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
						"assets/empty.xpm", &width, &height);
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == 'E' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, img_ptr, j
					* 4, i * 4);
			j++;
		}
		i++;
	}
	mlx_destroy_image(map->mlx_ptr, img_ptr);
}
