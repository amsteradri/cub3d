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

        if (current_length > longest_length) {
            longest_length = current_length;
        }
    }

    return longest_length;
}

void	init_vars(t_map *map)
{
	map->y = map_height(map->map);
	map->x = find_longest_line_length(map->map);
	map->player = (t_player *)malloc(sizeof(t_player));
	map->player->i_pj = 0;
	map->player->j_pj = 0;
	map->player->vect_x = 0;
	map->player->vect_y = 0;
	map->player->len_to_wall = 0;
	map->player->camera_angle = -50;
	map->player->rotation_angle = 0;
}

int	main(int argc, char **argv)
{
	(void)argv;
	// int i;

	// i = 0;
	t_map map;
	error_args(argc);
	check_ext(argv[1]);
	map.map = read_map(argv[1]);
	init_vars(&map);
	all_checks(&map);
	fill_dir(&map);
	init_window(&map);
	
	// while(map.map[i])
	// {
	// 	printf("%s\n", map.map[i]);
	// 	i++;
	// }
	// return(0);
}