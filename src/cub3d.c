/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:15:36 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/24 14:30:47 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void   leak_check(void)
// {
//     system("leaks -q cub3d");
// }

int	main(int argc, char **argv)
{
	// atexit(leak_check);
	(void)argv;
	t_map	map;

	error_args(argc);
	check_ext(argv[1]);
	map.map = read_map(argv[1]);
	parse_colors_and_directions(&map);
	map.map = &map.map[find_first_map_row(&map)];
	inits_structs(&map);
	all_checks(&map);
	fill_dir(&map);
	mlx_functions(&map);
}