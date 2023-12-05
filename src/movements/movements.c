/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:55:56 by isromero          #+#    #+#             */
/*   Updated: 2023/12/05 15:36:14 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_move(int fil, int col, t_map *map)
{
	if (fil < 0 || fil >= map->y || col < 0 || col >= map->x)
		return (0);
	if (map->map[fil][col] == '1')
		return (0);
	return (1);
}

static void move_forward(t_map *map)
{
    double new_x = map->player->x + cos(map->ray->angle);
    double new_y = map->player->y + sin(map->ray->angle);

    if (is_valid_move((int)new_y, (int)new_x, map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void move_backward(t_map *map)
{
    double new_x = map->player->x - cos(map->ray->angle);
    double new_y = map->player->y - sin(map->ray->angle);

    if (is_valid_move((int)new_y, (int)new_x, map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void move_left(t_map *map)
{
    double new_x = map->player->x - sin(map->ray->angle);
    double new_y = map->player->y + cos(map->ray->angle);

    if (is_valid_move((int)new_y, (int)new_x, map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void move_right(t_map *map)
{
    double new_x = map->player->x + sin(map->ray->angle);
    double new_y = map->player->y - cos(map->ray->angle);

    if (is_valid_move((int)new_y, (int)new_x, map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void	move_camera_left(t_map *map)
{
	map->ray->angle -= 3 * DR;
	if (map->ray->angle < 0)
		map->ray->angle += (2 * M_PI);
}

static void move_camera_right(t_map *map)
{
	map->ray->angle += 3 * DR;
	if (map->ray->angle >= M_PI * 2)
		map->ray->angle -= (2 * M_PI);
}

int	move_character(int keycode, t_map *map)
{
	if (keycode == 53)
		handle_esc_screen(map);
	else if (keycode == 0)
		move_right(map);
	else if (keycode == 13)
		move_forward(map);
	else if (keycode == 2)
		move_left(map);
	else if (keycode == 1)
		move_backward(map);
	else  if (keycode == 123)
		move_camera_left(map);
	else if (keycode == 124)
		move_camera_right(map);
	return (0);
}

// int move_character(int keycode, t_map *map)
// {
//      if (keycode == KEY_ESC)
//         handle_esc_screen(map);
//     else if (keycode == KEY_A)
//         move_left(map);
//     else if (keycode == KEY_W)
//         move_up(map);
//     else if (keycode == KEY_D)
//         move_right(map);
//     else if (keycode == KEY_S)
//         move_down(map);
//     else if (keycode == KEY_LEFT_ARROW)
//         move_camera_left(map);
//     else if (keycode == KEY_RIGHT_ARROW)
//         move_camera_right(map);

//     return (0);
// }