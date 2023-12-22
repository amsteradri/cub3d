/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:28:36 by isromero          #+#    #+#             */
/*   Updated: 2023/12/22 20:59:58 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_map *map, t_img *img, char *path)
{
	int	width;
	int	height;

	img->img = mlx_xpm_file_to_image(map->mlx_ptr, path, &width, &height);
	if (!img->img)
	{
		printf("Error loading texture, check if it exists\n");
		exit(1);
	}
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	initialize_textures(t_map *map)
{
	if (!map->no[0])
		load_texture(map, map->no_img, "assets/default.xpm");
	else
		load_texture(map, map->no_img, map->no);
	if (!map->we[0])
		load_texture(map, map->we_img, "assets/default.xpm");
	else
		load_texture(map, map->we_img, map->we);
	if (!map->ea[0])
		load_texture(map, map->ea_img, "assets/default.xpm");
	else
		load_texture(map, map->ea_img, map->ea);
	if (!map->so[0])
		load_texture(map, map->so_img, "assets/default.xpm");
	else
		load_texture(map, map->so_img, map->so);
	load_texture(map, map->char_2d, "assets/empty.xpm");
	load_texture(map, map->wall_2d, "assets/wall.xpm");
	load_texture(map, map->back_2d, "assets/fondo.xpm");
}

int	create_rgb_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

void	calculate_draw_values(t_map *map)
{
	map->draw->line_height = (int)(map->screen_height
			/ map->ray->perp_wall_dist);
	map->draw->draw_start = -map->draw->line_height / 2 + map->screen_height
		/ 2;
	if (map->draw->draw_start < 0)
		map->draw->draw_start = 0;
	map->draw->draw_end = map->draw->line_height / 2 + map->screen_height / 2;
	if (map->draw->draw_end >= map->screen_height)
		map->draw->draw_end = map->screen_height - 1;
}

void	texture_on_img(t_map *map, t_img *img)
{
	int	scale;

	scale = map->line->y * img->line_length - (900 * 1.0) * img->line_length / 2
		+ map->draw->line_height * img->line_length / 2;
	map->line->tex_y = ((scale * img->height) / map->draw->line_height)
		/ img->line_length;
	if (map->line->tex_y < 0 || map->line->tex_y >= img->height
		|| map->line->tex_x < 0 || map->line->tex_x >= img->width)
		return ;
	map->img->addr[map->line->y * map->img->line_length + map->line->x
		* map->img->bits_per_pixel / 8] = img->addr[map->line->tex_y
		* img->line_length + map->line->tex_x * (img->bits_per_pixel / 8)];
	map->img->addr[map->line->y * map->img->line_length + map->line->x
		* (map->img->bits_per_pixel / 8) + 1] = img->addr[map->line->tex_y
		* img->line_length + map->line->tex_x * (img->bits_per_pixel / 8) + 1];
	map->img->addr[map->line->y * map->img->line_length + map->line->x
		* (map->img->bits_per_pixel / 8) + 2] = img->addr[map->line->tex_y
		* img->line_length + map->line->tex_x * (img->bits_per_pixel / 8) + 2];
}
