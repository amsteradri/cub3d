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
	map->screen_width = map->x * 20;
	map->player = (t_player *)malloc(sizeof(t_player));
	map->player->i_pj = 0;
	map->player->j_pj = 0;
	map->player->vect_x = 0;
	map->player->vect_y = 0;
	map->player->len_to_wall = 0;
	map->player->camera_angle = -50;
	map->player->rotation_angle = 0;
	map->player->move_up = 0;
	map->player->move_left = 0;
	map->player->move_right = 0;
	map->player->move_down = 0;
	map->player->move_camera_left = 0;
	map->player->move_camera_right = 0;
}

void	init_vars_ray(t_ray *ray, t_map *map)
{
	ray->pos_x = map->player->j_pj;
	ray->pos_y = map->player->i_pj;
	ray->dir_x = map->player->vect_x;
	ray->dir_y = map->player->vect_y;
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = map->player->j_pj;
	ray->map_y = map->player->i_pj;
}

void	init_vars_line(t_line *line)
{
	line = (t_line *)malloc(sizeof(t_line));
	line->x = 0;
	line->y = 0;
	line->y0 = 0;
	line->y1 = 0;
	line->tex_x = 0;
	line->tex_y = 0;
	line->wall_x = 0;
}

// void   leak_check(void)
// {
//     system("leaks cub3d");
// }

int	main(int argc, char **argv)
{
	// atexit(leak_check);
	(void)argv;
	// int i;

	// i = 0;
	t_map map;
	t_ray ray;
	t_line line;

	error_args(argc);
	check_ext(argv[1]);
	map.map = read_map(argv[1]);
	init_vars_map(&map);
	init_vars_ray(&ray, &map);
	init_vars_line(&line);
	all_checks(&map);
	fill_dir(&map);
	init_window(&map, &ray, &line);
	
	
	// while(map.map[i])
	// {
	// 	printf("%s\n", map.map[i]);
	// 	i++;
	// }
	// return(0);
}