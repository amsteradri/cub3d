/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:15:36 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/18 20:06:19 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_textures(t_map *map)
{
	if (!map->no[0])
        ft_strncpy(map->no, "assets/default.xpm", sizeof(map->no) - 1);
	load_texture(map, map->no_img, map->no);
	if (!map->we[0])
		ft_strncpy(map->we, "assets/default.xpm", sizeof(map->we) - 1);
	load_texture(map, map->we_img, map->we);
	if (!map->ea[0])
		ft_strncpy(map->ea, "assets/default.xpm", sizeof(map->ea) - 1);
	load_texture(map, map->ea_img, map->ea);
	if (!map->so[0])
		ft_strncpy(map->so, "assets/default.xpm", sizeof(map->so) - 1);
	load_texture(map, map->so_img, map->so);
}

void	initialize_images_2d(t_map *map)
{
	load_texture(map, map->char_2d, "assets/empty.xpm");
	load_texture(map, map->wall_2d, "assets/wall.xpm");
	load_texture(map, map->back_2d, "assets/fondo.xpm");
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

int	find_longest_line_length(char **map)
{
	int	longest_length;
	int	current_length;

	longest_length = 0;
	if (map == NULL)
	{
		return (longest_length);
	}
	for (int i = 0; map[i] != NULL; i++)
	{
		current_length = strlen(map[i]);
		if (current_length > longest_length)
			longest_length = current_length;
	}
	return (longest_length);
}

void	init_vars_map(t_map *map)
{
	map->y = map_height(map->map);
	map->x = find_longest_line_length(map->map);
	map->screen_width = 1600;
	map->screen_height = 900;
	map->mlx_ptr = NULL;
	map->win_ptr = NULL;
	map->img = (t_img *)malloc(sizeof(t_img));
	map->img->img = NULL;
	map->img->addr = NULL;
	map->img->bits_per_pixel = 0;
	map->img->line_length = 0;
	map->img->endian = 0;
	map->img->height = 0;
	map->img->width = 0;
	map->texture = (t_img *)malloc(sizeof(t_img));
	map->texture->img = NULL;
	map->texture->addr = NULL;
	map->texture->bits_per_pixel = 0;
	map->texture->line_length = 0;
	map->texture->endian = 0;
	map->texture->height = 0;
	map->texture->width = 0;
	map->player = (t_player *)malloc(sizeof(t_player));
	map->player->y = 0.0;
	map->player->x = 0.0;
	map->player->dir_x = 0.0;
	map->player->dir_y = 0.0;
	map->player->plane_x = 0.0;
	map->player->plane_y = 0.0;
	map->ray = (t_ray *)malloc(sizeof(t_ray));
	map->ray->side = 0;
	map->ray->dir_x = 0.0;
	map->ray->dir_y = 0.0;
	map->ray->delta_dist_x = 0.0;
	map->ray->delta_dist_y = 0.0;
	map->ray->side_dist_x = 0.0;
	map->ray->side_dist_y = 0.0;
	map->ray->perp_wall_dist = 0.0;
	map->ray->step_x = 0;
	map->ray->step_y = 0;
	map->ray->map_x = 0;
	map->ray->map_y = 0;
	map->ray->hit = 0;
	map->ray->wall_x = 0.0;
	map->ray->col = 0;
	map->line = (t_line *)malloc(sizeof(t_line));
	map->line->x = 0;
	map->line->y = 0;
	map->line->y0 = 0;
	map->line->y1 = 0;
	map->line->tex_x = 0;
	map->line->tex_y = 0;
	map->draw = (t_draw *)malloc(sizeof(t_draw));
	map->draw->line_height = 0;
	map->draw->draw_start = 0;
	map->draw->draw_end = 0;
	map->no_img = (t_img *)malloc(sizeof(t_img));
	map->we_img = (t_img *)malloc(sizeof(t_img));
	map->ea_img = (t_img *)malloc(sizeof(t_img));
	map->so_img = (t_img *)malloc(sizeof(t_img));
	map->char_2d = (t_img *)malloc(sizeof(t_img));
	map->wall_2d = (t_img *)malloc(sizeof(t_img));
	map->back_2d = (t_img *)malloc(sizeof(t_img));
}

// void   leak_check(void)
// {
//     system("leaks -q cub3d");
// }

int	main(int argc, char **argv)
{
	//atexit(leak_check);
	(void)argv;
	t_map map;

	error_args(argc);
	check_ext(argv[1]);
	map.map = read_map(argv[1]);
	parse_top_map(&map);
	// printf("color:%d\n", map.fr);
	// int i = 0;
	// int j = 0;
	// while(map.map[i])
	// {
	// 	j = 0;
	// 	while(map.map[i][j])
	// 	{
	// 		printf("%d ", map.map[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }

	// printf("ESTO ES LA i %d\n", i);
	map.map = &map.map[find_first_map_row(&map)];
	//printf("LINE:%s\n", map.map[0]);
	init_vars_map(&map);
	all_checks(&map);
	fill_dir(&map);
	create_window(&map);
	create_img(&map);
	initialize_textures(&map);
	initialize_images_2d(&map); // Causa seg fault al utilizarlo en las funciones del minimapa (render2d.c)
	render_all(&map);
	mlx_hook(map.win_ptr, 2, 1L << 0, move_character, &map);
	mlx_hook(map.win_ptr, 17, 1L << 0, handle_esc_screen, &map);
	mlx_loop_hook(map.mlx_ptr, render_all, &map);
	mlx_loop(map.mlx_ptr);
	mlx_destroy_image(map.mlx_ptr, map.img->img);
	mlx_destroy_image(map.mlx_ptr, map.wall_2d->img);
	mlx_destroy_image(map.mlx_ptr, map.back_2d->img);
	mlx_destroy_image(map.mlx_ptr, map.char_2d->img);
}