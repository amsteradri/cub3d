/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:17:53 by adgutier          #+#    #+#             */
/*   Updated: 2023/10/17 16:15:40 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, (map->x * 20),
			(map->y * 20 + 2), "juego");
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

void draw_ray(t_map *map, int j, int i) 
{
    int x_end; 

	x_end = map->x * 20; 
    while (j < x_end) 
	{
		if (map->map[i / 20][j / 20] == '1') 
		{
            break; // Sale del bucle si encuentra una pared
        }
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, j, i, 0xFF0000); // Color rojo (formato RGB)
        j++;
    }
}

#include <math.h>

#include <math.h>

void draw_diagonal_line(t_map *map, double angle, int i, int j) 
{
    double player_x = j;  // Posición X del jugador
    double player_y = i;  // Posición Y del jugador

    int x_end = map->x * 20;
    
    while (player_x < x_end) {
        // Calcula las coordenadas (x, y) a lo largo de la línea diagonal
        double x = player_x + cos(angle * M_PI / 180.0);
        double y = player_y + sin(angle * M_PI / 180.0);

        int map_x = x / 20; // Convierte la posición X a coordenadas del mapa
        int map_y = y / 20; // Convierte la posición Y a coordenadas del mapa

        if (map->map[map_y][map_x] == '1') {
            map->player->len_to_wall = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));
            break;
        }

        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0xFF0000); // Color rojo (formato RGB)
        player_x = x;
        player_y = y;
    }
}



void	print_char_on_map(t_map *map)
{
	void	*img_ptr;
	int		width;
	int		height;
	double	angle;
	int		i;
	int		j;

	i = 0;
	j = 0;
	angle = 50;
	while (i < map->y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == 'E')
			{
				img_ptr = mlx_xpm_file_to_image(map->mlx_ptr,
						"assets/rojo.xpm", &width, &height);
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					img_ptr, j * 20, i * 20);
				draw_ray(map, j * 20, i * 20 + 10);
				draw_diagonal_line(map, 50, i * 20 , j * 20 + 10);
				while(angle > -50)
				{
					draw_diagonal_line(map, angle, i * 20 + 10 , j * 20 + 20);
					angle--;
				}
				draw_diagonal_line(map, -50, i * 20 + 10, j * 20 + 20);
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

void	render_all(t_map *map)
{
    draw_background(map);
	print_empty_on_map(map);
	print_obstacles_on_map(map);
	print_char_on_map(map);
}

int	is_valid_move(int fil, int col, t_map *map)
{
	if (fil < 0 || fil >= map->y || col < 0 || col >= map->x)
		return (0);
	if (map->map[fil][col] == '1')
		return (0);
	return (1);
}

static void	move_left(t_map *map)
{
	if (is_valid_move(map->player->i_pj, map->player->j_pj - 1, map))
	{
		map->map[map->player->i_pj][map->player->j_pj] = '0';
		map->player->j_pj--;
		map->map[map->player->i_pj][map->player->j_pj] = 'E';
		
	}
}

static void	move_up(t_map *map)
{
	if (is_valid_move(map->player->i_pj - 1, map->player->j_pj, map))
	{
		
		map->map[map->player->i_pj][map->player->j_pj] = '0';
		map->player->i_pj--;
		map->map[map->player->i_pj][map->player->j_pj] = 'E';
		
	}
}

static void	move_right(t_map *map)
{
	if (is_valid_move(map->player->i_pj, map->player->j_pj + 1, map))
	{
		map->map[map->player->i_pj][map->player->j_pj] = '0';
		map->player->j_pj++;
		map->map[map->player->i_pj][map->player->j_pj] = 'E';
		
	}
}

static void	move_down(t_map *map)
{
	if (is_valid_move(map->player->i_pj + 1, map->player->j_pj, map))
	{
		map->map[map->player->i_pj][map->player->j_pj] = '0';
		map->player->i_pj++;
		map->map[map->player->i_pj][map->player->j_pj] = 'E';
	}
}

int	move_character_up(int keycode, t_map *map)
{
	if (keycode == 0 || keycode == 123)
	{
		move_left(map);
	}
	else if (keycode == 13 || keycode == 126)
		move_up(map);
	else if (keycode == 2 || keycode == 124)
	{
		move_right(map);
	}
	else if (keycode == 1 || keycode == 125)
	{
		move_down(map);
	}
	render_all(map);
	return (0);
}

void	init_window(t_map *map)
{
	create_window(map);
	draw_background(map);
    render_all(map);
    mlx_key_hook(map->win_ptr, move_character_up, map);
	mlx_loop(map->mlx_ptr);
}