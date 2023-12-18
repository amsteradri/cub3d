/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:43 by isromero          #+#    #+#             */
/*   Updated: 2023/12/18 20:09:19 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int render_all(t_map *map) {
    static int counter = 0; // Contador de iteraciones

    raycast(map);
    //render_back_2d(map);
    render_walls_2d(map);
    // printf("columna: %d, fila : %d, ancho total: %d altura total: %d\n", i, j, map->y, (int)ft_strlen(map->map[i]));
    // Ejecutar cada 5 iteraciones
    if (counter % 5 == 0)
        render_char_2d(map);
    counter++; // Incrementa el contador en cada llamada a la función
    return (0);
}