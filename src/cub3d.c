/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:15:36 by adgutier          #+#    #+#             */
/*   Updated: 2023/10/07 18:15:36 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    int longest_length = 0;

    if (map == NULL) {
        return longest_length;
    }

    for (int i = 0; map[i] != NULL; i++) {
        int current_length = strlen(map[i]);

        if (current_length > longest_length)
            longest_length = current_length;
    }
    return longest_length;
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
	map->player = (t_player *)malloc(sizeof(t_player));
	map->player->y = 0.0;
	map->player->x = 0.0;
	map->line = (t_lines *)malloc(sizeof(t_lines));
	map->line->line_h.intersection_x = 0.0;
	map->line->line_v.intersection_x = 0.0;
	map->line->line_h.intersection_y = 0.0;
	map->line->line_v.intersection_y = 0.0;
	map->line->line_h.xa = 0.0;
	map->line->line_v.xa = 0.0;
	map->line->line_h.ya = 0.0;
	map->line->line_v.ya = 0.0;
	map->line->line_h.perp_dist = 0.0;
	map->line->line_v.perp_dist = 0.0;
	map->line->line_h.correct_dist = 0.0;
	map->line->line_v.correct_dist = 0.0;
	map->ray = (t_ray *)malloc(sizeof(t_ray));
	map->ray->x = 0.0;
	map->ray->y = 0.0;
	map->ray->angle = 0.0;
	map->ray->angle_between_rays = (60.0 / map->screen_width) * (M_PI / 180.0);
	map->ray->dist_player_projection_plane = (map->screen_width) / tan(30 * (M_PI / 180.0));
	map->ray->current_col = 0;
	map->ray->dist_to_slice = 0.0;
}

// void   leak_check(void)
// {
//     system("leaks cub3d");
// }

int	main(int argc, char **argv)
{
	// atexit(leak_check);
	(void)argv;
	t_map	map;

	error_args(argc);
	check_ext(argv[1]);
	map.map = read_map(argv[1]);
	parse_top_map(&map);
	// printf("color:%d\n", map.fr);
	map.map = &map.map[find_first_map_row(&map)];
	init_vars_map(&map);
	all_checks(&map);
	fill_dir(&map);
	create_window(&map);
	create_img(&map);
	render_all(&map);
	mlx_hook(map.win_ptr, 2, 1L << 0, move_character, &map);
	mlx_hook(map.win_ptr, 17, 1L << 0, handle_esc_screen, &map);
	mlx_loop_hook(map.mlx_ptr, render_all, &map);
	mlx_loop(map.mlx_ptr);
	mlx_destroy_image(map.mlx_ptr, map.img->img);
}