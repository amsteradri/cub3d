/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:43 by isromero          #+#    #+#             */
/*   Updated: 2023/12/14 14:56:59 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int render_all(t_map *map) {
    static int counter = 0; // Contador de iteraciones

    raycast(map);
	//render_background_2d(map);
    //render_empty_2d(map);
    render_walls_2d(map);
    // Ejecutar cada 5 iteraciones
    if (counter % 5 == 0) {
        
        render_char_2d(map);
    }

    counter++; // Incrementa el contador en cada llamada a la función
    return (0);
}