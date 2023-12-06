/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:28:36 by isromero          #+#    #+#             */
/*   Updated: 2023/12/06 15:52:53 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_texture(t_map *map, char *path)
{
    map->texture->img = mlx_xpm_file_to_image(map->mlx_ptr, path, &map->texture->width, &map->texture->height);
    if (!map->texture->img)
    {
        perror("Error cargando la textura");
        exit(EXIT_FAILURE);
    }

    map->texture->addr = mlx_get_data_addr(map->texture->img, &map->texture->bits_per_pixel, &map->texture->line_length, &map->texture->endian);
}

int get_texture_pixel_color(t_map *map, int x, int y)
{
    char *color = map->texture->addr + (y * map->texture->line_length + x * (map->texture->bits_per_pixel / 8));

    // Utilizamos máscaras para extraer los componentes RGBA
    unsigned char red = (unsigned char)color[0];
    unsigned char green = (unsigned char)color[1];
    unsigned char blue = (unsigned char)color[2];
    unsigned char alpha = (unsigned char)color[3];

    // Combinamos los componentes para obtener el color en formato RGBA
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}


void draw_vertical_line_with_texture(t_map *map, int x, int y, int texture_y)
{
	int pixel = (y * map->img->line_length) + (x * 4);

	// Asegurarse de que la coordenada de textura esté en el rango de la imagen de textura
	int texture_x = (int)((double)x / (double)map->screen_width * map->texture->width);
	if (texture_x >= map->texture->width)
		texture_x = map->texture->width - 1;

	int texture_color = get_texture_pixel_color(map, texture_x, texture_y);

	map->img->addr[pixel + 0] = (texture_color >> 24);
	map->img->addr[pixel + 1] = (texture_color >> 16) & 0xFF;
	map->img->addr[pixel + 2] = (texture_color >> 8) & 0xFF;
	map->img->addr[pixel + 3] = (texture_color) & 0xFF;
}


void draw_image_with_textures(t_map *map, int x, int projected_slice_height)
{
    int color_sky = 0xABCDEF;

    if (map->img->bits_per_pixel != 32)
        color_sky = mlx_get_color_value(map->mlx_ptr, color_sky);

    int color_floor = 0x00FF00;
    if (map->img->bits_per_pixel != 32)
        color_floor = mlx_get_color_value(map->mlx_ptr, color_floor);

    int ceiling_height = (map->screen_height - projected_slice_height) / 2;
    int floor_height = map->screen_height - ceiling_height;
	
    for (int y = 0; y < ceiling_height; y++)
    {
        int pixel = (y * map->img->line_length) + (x * 4);

        if (map->img->endian == 1)
        {
            map->img->addr[pixel + 0] = (color_sky >> 24);
            map->img->addr[pixel + 1] = (color_sky >> 16) & 0xFF;
            map->img->addr[pixel + 2] = (color_sky >> 8) & 0xFF;
            map->img->addr[pixel + 3] = (color_sky) & 0xFF;
        }
        else if (map->img->endian == 0)
        {
            map->img->addr[pixel + 0] = (color_sky) & 0xFF;
            map->img->addr[pixel + 1] = (color_sky >> 8) & 0xFF;
            map->img->addr[pixel + 2] = (color_sky >> 16) & 0xFF;
            map->img->addr[pixel + 3] = (color_sky >> 24);
        }
    }

    for (int y = ceiling_height; y < floor_height; y++)
    {
        // Calcular las coordenadas de textura en función de la altura de la pared proyectada
        double texture_scale = (double)(y - ceiling_height) / (double)(floor_height - ceiling_height);
        int texture_y = (int)(texture_scale * map->texture->height);

        draw_vertical_line_with_texture(map, x, y, texture_y);
    }

    for (int y = floor_height; y < map->screen_height; y++)
    {
        int pixel = (y * map->img->line_length) + (x * 4);

        if (map->img->endian == 1)
        {
            map->img->addr[pixel + 0] = (color_floor >> 24);
            map->img->addr[pixel + 1] = (color_floor >> 16) & 0xFF;
            map->img->addr[pixel + 2] = (color_floor >> 8) & 0xFF;
            map->img->addr[pixel + 3] = (color_floor) & 0xFF;
        }
        else if (map->img->endian == 0)
        {
            map->img->addr[pixel + 0] = (color_floor) & 0xFF;
            map->img->addr[pixel + 1] = (color_floor >> 8) & 0xFF;
            map->img->addr[pixel + 2] = (color_floor >> 16) & 0xFF;
            map->img->addr[pixel + 3] = (color_floor >> 24);
        }
    }
}
