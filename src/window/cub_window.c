/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:17:53 by adgutier          #+#    #+#             */
/*   Updated: 2023/11/16 08:43:21 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	create_window(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, (map->x * 16),
			(map->y * 16), "cub3d");
}

int	handle_esc_screen(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit(0);
}

void	init_window(t_map *map)
{
	create_window(map);
	/* render_background_2d(map); */
    render_all(map);
	mlx_hook(map->win_ptr, 2, 1L << 0, move_character, map);
	// Esto es para probar varias teclas, por ahora causa seg fault
	// mlx_hook(map->win_ptr, 2, 1L << 0, handle_key_press, map);
	// mlx_hook(map->win_ptr, 3, 1L << 1, handle_key_release, map);
    // mlx_loop_hook(map->win_ptr, move_character, map);
	mlx_hook(map->win_ptr, 17, 1L << 0, handle_esc_screen, map);
	mlx_loop(map->mlx_ptr);
}