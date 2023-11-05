/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:17:53 by adgutier          #+#    #+#             */
/*   Updated: 2023/11/05 15:15:15 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, (map->x * 20),
			(map->y * 20 + 2), "cub3d");
}

void	draw_background(t_map *map)
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
	while (j < (map->y * 20 + 2))
	{
		i = 0;
		while (i < (map->x * 20))
		{
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, img_ptr, i, j);
			i = i + 20;
		}
		j = j + 20;
	}
	mlx_destroy_image(map->mlx_ptr, img_ptr);
}

void	print_empty_on_map(t_map *map)
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
					img_ptr, j * 20, i * 20);
				mlx_destroy_image(map->mlx_ptr, img_ptr);
			}
			j++;
		}
		i++;
	}
}

void	print_obstacles_on_map(t_map *map)
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
						"assets/muro.xpm", &width, &height);
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					img_ptr, j * 20, i * 20);
				mlx_destroy_image(map->mlx_ptr, img_ptr);
			}
			j++;
		}
		i++;
	}
}

void	print_char_on_map(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	// double	angle;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// angle = -50;
	map->player->camera_angle = -50 + map->player->rotation_angle;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == 'E') // Habría que hacer en todas las direcciones
			{
				img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
						"assets/rojo.xpm", &width, &height);
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					img_ptr, j * 20, i * 20);
				// draw_ray(map, j * 20, i * 20 + 10);
				// draw_diagonal_line(map, 50, i * 20 , j * 20 + 10);
				while(map->player->camera_angle <= (50 + map->player->rotation_angle))
				{
					draw_diagonal_line(map, map->player->camera_angle, i * 20 + 10 , j * 20 + 20);
					map->player->camera_angle++;
				}
				// draw_diagonal_line(map, -50, i * 20 + 10, j * 20 + 20);
				mlx_destroy_image(map->mlx_ptr, img_ptr);
			}
			j++;
		}
		i++;
	}
}

void	render_all(t_map *map)
{
    draw_background(map);
	print_empty_on_map(map);
	print_obstacles_on_map(map);
	print_char_on_map(map);
}

int	handle_esc_screen(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit(0);
}

void	init_window(t_map *map)
{
	create_window(map);
	draw_background(map);
    render_all(map);
	mlx_hook(map->win_ptr, 2, 1L << 0, move_character, map);
	// Esto es para probar varias teclas, por ahora causa seg fault
	// mlx_hook(map->win_ptr, 2, 1L << 0, handle_key_press, map);
	// mlx_hook(map->win_ptr, 3, 1L << 1, handle_key_release, map);
    // mlx_loop_hook(map->win_ptr, move_character, map);
	mlx_hook(map->win_ptr, 17, 1L << 0, handle_esc_screen, map);
	mlx_loop(map->mlx_ptr);
}