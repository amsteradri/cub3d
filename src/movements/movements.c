/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:54:13 by isromero          #+#    #+#             */
/*   Updated: 2024/03/17 11:09:39 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_map *map)
{
	double	new_x;
	double	new_y;

	map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x + map->player->dir_x * 0.6;
	new_y = map->player->y + map->player->dir_y * 0.6;
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
	map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

void toggle_door(t_map *map) {
    int dx[] = {0, 1, 0, -1, 1, 1, -1, -1}; // Direcciones X para verificar alrededor del jugador
    int dy[] = {1, 0, -1, 0, 1, -1, 1, -1}; // Direcciones Y para verificar alrededor del jugador
    int door_found = 0; // Bandera para indicar si se encontró una puerta para cambiar
    int new_x, new_y; // Nuevas coordenadas X y Y para verificar

    // Verifica alrededor del jugador, incluyendo diagonales
    for (int i = 0; i < 8 && !door_found; ++i) {
        new_x = (int)map->player->x + dx[i]; // Calcula la nueva coordenada X basada en la dirección
        new_y = (int)map->player->y + dy[i]; // Calcula la nueva coordenada Y basada en la dirección

        // Si encuentra una puerta cerrada ('c'), la abre ('o')
        if (map->map[new_y][new_x] == 'c') {
            map->map[new_y][new_x] = 'o'; // Cambia la puerta cerrada por abierta
            door_found = 1; // Establece la bandera a 1 para indicar que se cambió el estado de una puerta
        }
        // Si encuentra una puerta abierta ('o'), la cierra ('c')
        else if (map->map[new_y][new_x] == 'o') {
            map->map[new_y][new_x] = 'c'; // Cambia la puerta abierta por cerrada
            door_found = 1; // Establece la bandera a 1 para indicar que se cambió el estado de una puerta
        }
    }
}



void	move_backward(t_map *map)
{
	double	new_x;
	double	new_y;

	map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x - map->player->dir_x * 0.6;
	new_y = map->player->y - map->player->dir_y * 0.6;
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
	map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

void	move_right(t_map *map)
{
	double	new_x;
	double	new_y;

	map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x - map->player->dir_y * 0.6;
	new_y = map->player->y + map->player->dir_x * 0.6;
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
	map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
}

void	move_left(t_map *map)
{
	double	new_x;
	double	new_y;

	map->map[(int)map->player->y][(int)map->player->x] = '0';
	new_x = map->player->x + map->player->dir_y * 0.6;
	new_y = map->player->y - map->player->dir_x * 0.6;
	if (is_valid_move((int)map->player->y, (int)new_x, map))
		map->player->x = new_x;
	if (is_valid_move((int)new_y, (int)map->player->x, map))
		map->player->y = new_y;
	map->map[(int)map->player->y][(int)map->player->x] = map->player->dir;
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
	else if (keycode == 14)
		toggle_door(map);
	return (0);
}

// int move_character(int keycode, t_map *map)
// {
// 		if (keycode == KEY_ESC)
// 		handle_esc_screen(map);
// 	else if (keycode == KEY_W)
// 		move_forward(map);
// 	else if (keycode == KEY_S)
// 		move_backward(map);
// 	else if(keycode == KEY_A)
// 		move_left(map);
// 	else if(keycode == KEY_D)
// 		move_right(map);
// 	else if (keycode == KEY_LEFT_ARROW)
// 		move_camera_left(map);
// 	else if (keycode == KEY_RIGHT_ARROW)
// 		move_camera_right(map);
// 	return (0);
// }