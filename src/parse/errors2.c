/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:33:02 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 14:50:30 by isromero         ###   ########.fr       */
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
			print_error_and_exit("No walls in first col");
		if ((*map)->map[i][ft_strlen((*map)->map[i])
			- ft_spacelen((*map)->map[i]) - 1] != '1')
			print_error_and_exit("No walls in last col");
		i++;
	}
	first_line((*map)->map[(*map)->y - 1]);
}

int	is_valid_character(char c)
{
	return (c == '1' || c == '0' || c == 'E'
		|| c == 'N' || c == 'S' || c == 'W');
}

void	check_surrounding(t_map **map, int i, int j, int aux)
{
	int	len;

	len = ft_strlen((*map)->map[i]);
	if ((i + 1 <= aux) && !is_valid_character((*map)->map[i + 1][j]))
		print_error_and_exit("No walls in bot row");
	if ((*map)->map[i - 1][j] != '1' &&
		!is_valid_character((*map)->map[i - 1][j]))
		print_error_and_exit("No walls in top row");
	if (j + 1 <= len && !is_valid_character((*map)->map[i][j + 1]))
		print_error_and_exit("No walls in right col");
	if ((*map)->map[i][j - 1] != '1' &&
		!is_valid_character((*map)->map[i][j - 1]))
		print_error_and_exit("No walls in left col");
}

void	check_under_empty(t_map **map)
{
	int	i;
	int	aux;
	int	j;

	i = 1;
	j = 0;
	aux = (*map)->y - 1;
	while (i < aux)
	{
		j = 0;
		while (j < (int)ft_strlen((*map)->map[i]))
		{
			if ((*map)->map[i][j] == '0')
				check_surrounding(map, i, j, aux);
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
