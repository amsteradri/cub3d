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

void	init_vars(t_map *map)
{
	map->y = map_height(map->map);
	map->x = ft_strlen(map->map[0]);
}


int main(int argc, char **argv)
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
	// while(map.map[i])
	// {
	// 	printf("%s\n", map.map[i]);
	// 	i++;
	// }
	// return(0);

}