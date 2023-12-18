/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/0.1/28 08:55:56 by isromero          #+#    #+#             */
/*   Updated: 2023/12/06 14:01:29 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_move(int fil, int col, t_map *map)
{
	double margin = 0.4;
		// Margen para evitar que el jugador se acerque demasiado a las paredes
	// Verifica si las coordenadas están fuera de los límites del mapa
	if (fil < margin || fil >= map->y - margin || col < margin || col >= map->x
		- margin)
		return (0);
	// Verifica si la posición es una pared
	if (map->map[fil][col] == '1')
		return (0);
	return (1);
}

static void	move_forward(t_map *map)
{
	double	new_x;
	double	new_y;

    map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x + map->player->dir_x * 0.6;
	new_y = map->player->y + map->player->dir_y * 0.6;
	// Verificar colisión por separado para X y Y (Esto permite deslizarse por las paredes y no quedarse atascado)
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
    map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

static void	move_backward(t_map *map)
{
	double	new_x;
	double	new_y;

    map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x - map->player->dir_x * 0.6;
	new_y = map->player->y - map->player->dir_y * 0.6;
	// Verificar colisión por separado para X y Y (Esto permite deslizarse por las paredes y no quedarse atascado)
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
    map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

static void	move_right(t_map *map)
{
	double	new_x;
	double	new_y;

    map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x - map->player->dir_y * 0.6;
	new_y = map->player->y + map->player->dir_x * 0.6;
	// Verificar colisión por separado para X y Y (Esto permite deslizarse por las paredes y no quedarse atascado)
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
    map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

static void	move_left(t_map *map)
{
	double	new_x;
	double	new_y;

    map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x + map->player->dir_y * 0.6;
	new_y = map->player->y - map->player->dir_x * 0.6;
	// Verificar colisión por separado para X y Y (Esto permite deslizarse por las paredes y no quedarse atascado)
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
    map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

static void	move_camera_left(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->player->dir_x;
	map->player->dir_x = map->player->dir_x * cos(-(16 * DR))
		- map->player->dir_y * sin(-(16 * DR));
	map->player->dir_y = old_dir_x * sin(-(16 * DR)) + map->player->dir_y
		* cos(-(16 * DR));
	old_plane_x = map->player->plane_x;
	map->player->plane_x = map->player->plane_x * cos(-(16 * DR))
		- map->player->plane_y * sin(-(16 * DR));
	map->player->plane_y = old_plane_x * sin(-(16 * DR)) + map->player->plane_y
		* cos(-(16 * DR));
}

static void	move_camera_right(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->player->dir_x;
	map->player->dir_x = map->player->dir_x * cos(16 * DR) - map->player->dir_y
		* sin(16 * DR);
	map->player->dir_y = old_dir_x * sin(16 * DR) + map->player->dir_y * cos(16
			* DR);
	old_plane_x = map->player->plane_x;
	map->player->plane_x = map->player->plane_x * cos(16 * DR)
		- map->player->plane_y * sin(16 * DR);
	map->player->plane_y = old_plane_x * sin(16 * DR) + map->player->plane_y
		* cos(16 * DR);
}

int	move_character(int keycode, t_map *map)
{
	if (keycode == 53)
		handle_esc_screen(map);
	else if (keycode == 13)
		move_forward(map);
	else if (keycode == 1)
		move_backward(map);
	else if (keycode == 0)
		move_left(map);
	else if (keycode == 2)
		move_right(map);
	else if (keycode == 123)
		move_camera_left(map);
	else if (keycode == 124)
		move_camera_right(map);
	return (0);
}

/* int move_character(int keycode, t_map *map)
{
     if (keycode == KEY_ESC)
        handle_esc_screen(map);
    else if (keycode == KEY_W)
        move_forward(map);
    else if (keycode == KEY_S)
        move_backward(map);
    else if(keycode == KEY_A)
        move_left(map);
    else if(keycode == KEY_D)
        move_right(map);
    else if (keycode == KEY_LEFT_ARROW)
        move_camera_left(map);
    else if (keycode == KEY_RIGHT_ARROW)
        move_camera_right(map);
    return (0);
} */