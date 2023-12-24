/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:33:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 14:31:32 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls(t_map **map)
{
	int	i;
	int	aux;
	int	j;

	i = 1;
	j = 0;
	aux = (*map)->y - 1;
	first_line((*map)->map[0]);
	while (i < aux)
	{
		j = 0;
		while ((*map)->map[i][j] == ' ')
			j++;
		if ((*map)->map[i][j] != '1')
		{
			printf("\033[1;31mERROR: No walls in first col\033[0m\n");
			exit(1);
		}
		if ((*map)->map[i][ft_strlen((*map)->map[i])
			- ft_spacelen((*map)->map[i]) - 1] != '1')
		{
			printf("\033[1;31mERROR: No walls in last col\033[0m\n");
			exit(1);
		}
		i++;
	}
	first_line((*map)->map[(*map)->y - 1]);
}

void	check_under_empty(t_map **map)
{
	int	i;
	int	aux;
	int	j;
	int	len;

	i = 1;
	j = 0;
	aux = (*map)->y - 1;
	len = ft_strlen((*map)->map[i]);
	while (i < aux)
	{
		j = 0;
		len = ft_strlen((*map)->map[i]);
		while (j < len)
		{
			if ((*map)->map[i][j] == '0')
			{
				if ((i + 1 <= aux) && (*map)->map[i + 1][j] != '1'
					&& (*map)->map[i + 1][j] != '0' && (*map)->map[i
					+ 1][j] != 'E' && (*map)->map[i + 1][j] != 'N'
					&& (*map)->map[i + 1][j] != 'S' && (*map)->map[i
					+ 1][j] != 'W')
				{
					printf("\033[1;31mERROR: No walls in bot row\033[0m\n");
					exit(1);
				}
				if ((*map)->map[i - 1][j] != '1' && (*map)->map[i - 1][j] != '0'
					&& (*map)->map[i - 1][j] != 'E' && (*map)->map[i
					- 1][j] != 'N' && (*map)->map[i - 1][j] != 'S'
					&& (*map)->map[i - 1][j] != 'W')
				{
					printf("\033[1;31mERROR: No walls in top row\033[0m\n");
					exit(1);
				}
				if (j + 1 <= len && (*map)->map[i][j + 1] != '1'
					&& (*map)->map[i][j + 1] != '0' && (*map)->map[i][j
					+ 1] != 'E' && (*map)->map[i][j + 1] != 'N'
					&& (*map)->map[i][j + 1] != 'S' && (*map)->map[i][j
					+ 1] != 'W')
				{
					printf("\033[1;31mERROR: No walls in right col\033[0m\n");
					exit(1);
				}
				if ((*map)->map[i][j - 1] != '1' && (*map)->map[i][j - 1] != '0'
					&& (*map)->map[i][j - 1] != 'E' && (*map)->map[i][j
					- 1] != 'N' && (*map)->map[i][j - 1] != 'S'
					&& (*map)->map[i][j - 1] != 'W')
				{
					printf("\033[1;31mERROR: No walls in left col\033[0m\n");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

void	all_checks(t_map *map)
{
	check_chars(&map);
	check_nsew(&map);
	check_walls(&map);
	check_under_empty(&map);
}
