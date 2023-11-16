/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:43 by isromero          #+#    #+#             */
/*   Updated: 2023/11/16 08:42:47 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_all(t_map *map)
{
    /* render_background_2d(map); */
	/* render_empty_2d(map) */;
	/* render_walls_2d(map) */;
	/* render_char_2d(map); */
	raycast(map);
}