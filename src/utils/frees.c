/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:02:29 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 18:10:25 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		free(map->map[i]);
	free(map->map);
}

void	free_all(t_map *map)
{
	free_map(map);
	free(map->ray);
	free(map->draw);
	free(map->player);
	free(map->line);
	free(map->texture);
}
