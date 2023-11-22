/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:17:53 by adgutier          #+#    #+#             */
/*   Updated: 2023/11/22 08:24:30 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	create_window(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, 848,
			480, "cub3d");
}
void	create_img(t_map *map)
{
	map->img->img = mlx_new_image(map->mlx_ptr, 848, 480);
	// addr = buffer
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bits_per_pixel,
			&map->img->line_length, &map->img->endian);
}

int	handle_esc_screen(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit(0);
}