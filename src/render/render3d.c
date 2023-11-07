/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:23 by isromero          #+#    #+#             */
/*   Updated: 2023/11/07 18:53:58 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_all(t_map *map)
{
    render_background_2d(map);
	render_empty_2d(map);
	render_walls_2d(map);
	render_char_2d(map);
	// int n_rays = 60; // Cantidad de rayos en el campo de visión
    // double initial_angle = map->player->pa - (M_PI / 6);  // Ángulo inicial en radianes (aproximadamente 30 grados)

    // for (int ray_index = 0; ray_index < n_rays; ray_index++) {

    //     // Dibuja un rayo para el ángulo actual
    //     draw_diagonal_ray(map, initial_angle, map->player->i_pj * 20 + 10, map->player->j_pj * 20 + 10);
	// 	initial_angle += DR;
    // }
}