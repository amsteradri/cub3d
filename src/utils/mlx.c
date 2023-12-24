/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:46:31 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 12:41:02 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_img_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->img->addr + (y * map->img->line_length + x
			* (map->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	pixel_on_img(t_map *map, int rgb, int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel
		/ 8] = b;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8
		+ 1] = g;
	map->img->addr[y * map->img->line_length + x * map->img->bits_per_pixel / 8
		+ 2] = r;
}

void	mlx_hooks(t_map *map)
{
	mlx_hook(map->win_ptr, 2, 1L << 0, move_character, map);
	mlx_hook(map->win_ptr, 17, 1L << 0, handle_esc_screen, map);
	mlx_loop_hook(map->mlx_ptr, render_all, map);
	mlx_loop(map->mlx_ptr);
}

void	mlx_destroy_images(t_map *map)
{
	mlx_destroy_image(map->mlx_ptr, map->img->img);
	mlx_destroy_image(map->mlx_ptr, map->no_img->img);
	mlx_destroy_image(map->mlx_ptr, map->so_img->img);
	mlx_destroy_image(map->mlx_ptr, map->ea_img->img);
	mlx_destroy_image(map->mlx_ptr, map->we_img->img);
	mlx_destroy_image(map->mlx_ptr, map->char_2d->img);
	mlx_destroy_image(map->mlx_ptr, map->wall_2d->img);
	mlx_destroy_image(map->mlx_ptr, map->back_2d->img);
}

void	mlx_functions(t_map *map)
{
	create_window(map);
	create_img(map);
	initialize_textures(map);
	mlx_hooks(map);
	mlx_destroy_images(map);
}