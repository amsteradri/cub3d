/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:35:34 by adgutier          #+#    #+#             */
/*   Updated: 2024/04/07 12:03:32 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_direction(int delta_x, t_player *player)
{
	double	rotation_speed;
	double	old_dir_x;

	rotation_speed = delta_x * 0.005;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotation_speed)
		- player->dir_y * sin(rotation_speed);
	player->dir_y = old_dir_x * sin(rotation_speed)
		+ player->dir_y * cos(rotation_speed);
}

void	update_camera_plane(int delta_x, t_player *player)
{
	double	rotation_speed;
	double	old_plane_x;

	rotation_speed = delta_x * 0.005;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotation_speed)
		- player->plane_y * sin(rotation_speed);
	player->plane_y = old_plane_x * sin(rotation_speed)
		+ player->plane_y * cos(rotation_speed);
}

int	mouse_move(int x, int y, t_map *map)
{
	static int	last_x = -1;
	int			delta_x;

	if (x < 0 || y < 0 || x > map->screen_width || y > map->screen_height)
	{
		last_x = -1;
		return (0);
	}
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	update_player_direction(delta_x, map->player);
	update_camera_plane(delta_x, map->player);
	last_x = x;
	return (0);
}
