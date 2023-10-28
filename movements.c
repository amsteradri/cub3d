/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:55:56 by isromero          #+#    #+#             */
/*   Updated: 2023/10/28 08:59:31 by isromero         ###   ########.fr       */
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
