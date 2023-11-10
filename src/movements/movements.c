/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:55:56 by isromero          #+#    #+#             */
/*   Updated: 2023/11/10 21:12:06 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

static void	move_camera_left(t_map *map)
{
	map->player->angle -= 3 * DR;
	if (map->player->angle < 0)
		map->player->angle += (2 * M_PI);
}

static void move_camera_right(t_map *map)
{
	map->player->angle += 3 * DR;
	if (map->player->angle >= M_PI * 2)
		map->player->angle -= (2 * M_PI);
}

int	move_character(int keycode, t_map *map)
{
	if (keycode == 53)
		handle_esc_screen(map);
	else if (keycode == 0)
		move_left(map);
	else if (keycode == 13)
		move_up(map);
	else if (keycode == 2)
		move_right(map);
	else if (keycode == 1)
		move_down(map);
	else  if (keycode == 123)
		move_camera_left(map);
	else if (keycode == 124)
		move_camera_right(map);
	render_all(map);
	return (0);
}

// Esto de abajo es para probar con varias teclas, por ahora causa seg fault

// int	move_character(t_map *map)
// {
	
// 	if (map->player->move_left == 1)
// 		move_left(map);
// 	else if (map->player->move_up == 1)
// 		move_up(map);
// 	else if (map->player->move_right == 1)
// 		move_right(map);
// 	else if (map->player->move_down == 1)
// 		move_down(map);
// 	else  if (map->player->move_camera_left == 1)
// 		move_camera_left(map);
// 	else if (map->player->move_camera_right == 1)
// 		move_camera_right(map);
	
// 	return (0);
// }

// int	handle_key_press(int keycode, t_map *map)
// {
// 	if (keycode == 53)
// 		handle_esc_screen(map);
// 	else if (keycode == 0)
// 		map->player->move_left = 1;
// 	else if (keycode == 13)
// 		map->player->move_up = 1;
// 	else if (keycode == 2)
// 		map->player->move_right = 1;
// 	else if (keycode == 1)
// 		map->player->move_down = 1;
// 	else  if (keycode == 123)
// 		map->player->move_camera_left = 1;
// 	else if (keycode == 124)
// 		map->player->move_camera_right = 1;
// 	return (0);
// }

// int	handle_key_release(int keycode, t_map *map)
// {
// 	if (keycode == 53)
// 		handle_esc_screen(map);
// 	else if (keycode == 0 && map->player->move_left == 1)
// 		map->player->move_left = 0;
// 	else if (keycode == 13 && map->player->move_up == 1)
// 		map->player->move_up = 0;
// 	else if (keycode == 2 && map->player->move_right == 1)
// 		map->player->move_right = 0;
// 	else if (keycode == 1 && map->player->move_down == 1)
// 		map->player->move_down = 0;
// 	else  if (keycode == 123 && map->player->move_camera_left == 1)
// 		map->player->move_camera_left = 0;
// 	else if (keycode == 124 && map->player->move_right == 1)
// 		map->player->move_camera_right = 0;
// 	return (0);
// }