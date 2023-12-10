/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:28:36 by isromero          #+#    #+#             */
/*   Updated: 2023/12/10 21:29:53 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_map *map, char *path)
{
	int	width;
	int	height;

    //printf("%p\n", map->texture->img);
	map->texture->img = mlx_xpm_file_to_image(map->mlx_ptr, path, &width, &height);
    //printf("%d\n", width);
	if (!map->texture->img)
    {
        printf("Error loading texture\n");
        exit(1);
    }
	map->texture->width = width;
	map->texture->height = height;
	map->texture->addr = mlx_get_data_addr(map->texture->img, &map->texture->bits_per_pixel,
			&map->texture->line_length, &map->texture->endian);
}
