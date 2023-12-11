/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:28:36 by isromero          #+#    #+#             */
/*   Updated: 2023/12/11 17:52:01 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_map *map, t_img *img, char *path)
{
	int	width;
	int	height;

    //printf("%p\n", map->texture->img);
	img->img = mlx_xpm_file_to_image(map->mlx_ptr, path, &width, &height);
    //printf("%d\n", width);
	if (!img->img)
    {
        printf("Error loading texture\n");
        exit(1);
    }
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}
