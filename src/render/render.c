/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:43 by isromero          #+#    #+#             */
/*   Updated: 2023/12/19 12:37:37 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_all(t_map *map)
{
	raycast(map);
	render_walls_2d(map);
	render_char_2d(map);
	return (0);
}
