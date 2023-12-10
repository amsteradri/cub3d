/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:28:36 by isromero          #+#    #+#             */
/*   Updated: 2023/12/10 14:38:47 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *load_texture(t_map *map, char *path)
{
    t_img *texture = (t_img *)malloc(sizeof(t_img));  // Asigna memoria para la estructura
    if (!texture)
    {
        perror("Error en la asignación de memoria para la textura");
        exit(EXIT_FAILURE);
    }
    int width, height, unused;

    // Carga la textura con MLX
    texture->img = mlx_xpm_file_to_image(map->mlx_ptr, path, &width, &height);
    if (!texture->img)
    {
        // Manejo de error si la carga falla
        perror("Error cargando textura");
        exit(EXIT_FAILURE);
    }

    // Extrae la información de la textura
    texture->addr = mlx_get_data_addr(texture->img, &unused, &width, &unused);
    texture->width = width;
    texture->height = height;

    return texture;
}
