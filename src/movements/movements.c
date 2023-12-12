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
	if (fil < 0 || fil >= map->y || col < 0 || col >= map->x)
		return (0);
	if (map->map[fil][col] == '1')
		return (0);
	return (1);
}

static void move_forward(t_map *map)
{
    double new_x = map->player->x + map->player->dir_x * 0.2;
    double new_y = map->player->y + map->player->dir_y * 0.2;

    if (is_valid_move((int)(new_y), (int)(new_x), map))
    {
        // Movimiento hacia adelante si la nueva posición es válida
        map->player->x = new_x;
        map->player->y = new_y;
    }
   /*  else
    {
        // Ajusta el factor de separación para reducir la distancia al muro
        double separation_factor = 0.01;

        // Intenta moverse a lo largo del muro (ajusta según sea necesario)
        new_x = map->player->x + map->player->dir_y * separation_factor;
        new_y = map->player->y - map->player->dir_x * separation_factor;

        if (is_valid_move((int)(new_y), (int)(new_x), map))
        {
            map->player->x = new_x;
            map->player->y = new_y;
        }
        else
        {
            // Intenta moverse en la dirección opuesta a lo largo del muro
            new_x = map->player->x - map->player->dir_y * separation_factor;
            new_y = map->player->y + map->player->dir_x * separation_factor;

            if (is_valid_move((int)(new_y), (int)(new_x), map))
            {
                map->player->x = new_x;
                map->player->y = new_y;
            }
        }
    } */
}


static void move_backward(t_map *map)
{
    double new_x = map->player->x - map->player->dir_x * 0.2;
    double new_y = map->player->y - map->player->dir_y * 0.2;

    if (is_valid_move((int)floor(new_y), (int)floor(new_x), map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void move_right(t_map *map)
{
    double move_speed = 0.5;  // Ajusta esta velocidad según sea necesario
    double new_x = map->player->x - map->player->dir_y * move_speed;
    double new_y = map->player->y + map->player->dir_x * move_speed;

    if (is_valid_move((int)floor(new_y), (int)floor(new_x), map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void move_left(t_map *map)
{
    double move_speed = 0.5;  // Ajusta esta velocidad según sea necesario
    double new_x = map->player->x + map->player->dir_y * move_speed;
    double new_y = map->player->y - map->player->dir_x * move_speed;

    if (is_valid_move((int)floor(new_y), (int)floor(new_x), map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

/* static void move_left(t_map *map)
{
    double new_x = map->player->x - (sin(map->ray->angle) * 0.5);
    double new_y = map->player->y + (cos(map->ray->angle) * 0.5);

    if (is_valid_move((int)floor(new_y), (int)floor(new_x), map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
}

static void move_right(t_map *map)
{
    double new_x = map->player->x + (sin(map->ray->angle) * 0.5);
    double new_y = map->player->y - (cos(map->ray->angle) * 0.5);

    if (is_valid_move((int)floor(new_y), (int)floor(new_x), map))
    {
        map->player->x = new_x;
        map->player->y = new_y;
    }
} */


static void	move_camera_left(t_map *map)
{
	double old_dir_x = map->player->dir_x;
    map->player->dir_x = map->player->dir_x * cos(-(8 * DR)) - map->player->dir_y * sin(-(8 * DR));
    map->player->dir_y = old_dir_x * sin(-(8 * DR)) + map->player->dir_y * cos(-(8 * DR));
    double old_plane_x = map->player->plane_x;
    map->player->plane_x = map->player->plane_x * cos(-(8 * DR)) - map->player->plane_y * sin(-(8 * DR));
    map->player->plane_y = old_plane_x * sin(-(8 * DR)) + map->player->plane_y * cos(-(8 * DR));
}

static void move_camera_right(t_map *map)
{
	double old_dir_x = map->player->dir_x;
    map->player->dir_x = map->player->dir_x * cos(8 * DR) - map->player->dir_y * sin(8 * DR);
    map->player->dir_y = old_dir_x * sin(8 * DR) + map->player->dir_y * cos(8 * DR);
    double old_plane_x = map->player->plane_x;
    map->player->plane_x = map->player->plane_x * cos(8 * DR) - map->player->plane_y * sin(8 * DR);
    map->player->plane_y = old_plane_x * sin(8 * DR) + map->player->plane_y * cos(8 * DR);
}

int	move_character(int keycode, t_map *map)
{
	if (keycode == 53)
		handle_esc_screen(map);
	else if (keycode == 13)
		move_forward(map);
	else if (keycode == 1)
		move_backward(map);
    else if(keycode == 0)
        move_left(map);
    else if(keycode == 2)
        move_right(map);
	else  if (keycode == 123)
		move_camera_left(map);
	else if (keycode == 124)
		move_camera_right(map);
	return (0);
}

	/* else if (keycode == 2)
		move_left(map);
        else if (keycode == 0)
		move_right(map); */

// int move_character(int keycode, t_map *map)
// {
//      if (keycode == KEY_ESC)
//         handle_esc_screen(map);
//     else if (keycode == KEY_W)
//         move_forward(map);
//     else if (keycode == KEY_S)
//         move_backward(map);
//     else if(keycode == KEY_A)
//         move_left(map);
//     else if(keycode == KEY_D)
//         move_right(map);
//     else if (keycode == KEY_LEFT_ARROW)
//         move_camera_left(map);
//     else if (keycode == KEY_RIGHT_ARROW)
//         move_camera_right(map);
//     return (0);
// }