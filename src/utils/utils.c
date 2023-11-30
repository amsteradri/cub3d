/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:02:38 by isromero          #+#    #+#             */
/*   Updated: 2023/11/30 08:58:50 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_vertical_len(t_map *map, int col, int row)
{
	int	i;

	i = 0;
	if (col < 0 || col > (int)ft_strlen(map->map[row]))
			return (0);
	while(map->map[i][col])
	{
		if (col < 0 || col > (int)ft_strlen(map->map[i]))
			return (0);
		i++;
	}	
	return (i);
}