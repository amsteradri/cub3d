/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:25:52 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/24 14:38:59 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_args(int argc)
{
	if (argc == 1)
	{
		printf("\033[0;31mError\n\033[0m");
		printf("\033[0;31mNo input file given\n\033[0m");
		printf("\033[0;33mTry this format:./cub3d <map.cub>\n\033[0m");
		exit(1);
	}
	if (argc > 2)
	{
		printf("\033[0;31mError\n\033[0m");
		printf("\033[0;31mToo much arguments\n\033[0m");
		printf("\033[0;33mTry this format:./cub3d <map.cub>\n\033[0m");
		exit(1);
	}
}

void	check_ext(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (map[len - 4] != '.' || map[len - 3] != 'c' || map[len - 2] != 'u'
		|| map[len - 1] != 'b')
		print_error_and_exit("Wrong map extension");
}

void	check_chars(t_map **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < (*map)->y)
	{
		x = 0;
		while ((*map)->map[y][x] != '\0' && (*map)->map[y][x] != '\r')
		{
			if ((*map)->map[y][x] != '0' && (*map)->map[y][x] != '1'
				&& (*map)->map[y][x] != 'N' && (*map)->map[y][x] != 'E'
				&& (*map)->map[y][x] != 'S' && (*map)->map[y][x] != 'W'
				&& (*map)->map[y][x] != ' ')
				print_error_and_exit("Wrong map components");
			x++;
		}
		y++;
	}
}

void	check_nsew(t_map **map)
{
	int	y;
	int	x;
	int	direction_count;

	direction_count = 0;
	y = 0;
	while (y < (*map)->y && direction_count <= 1)
	{
		x = 0;
		while (x < (int)ft_strlen((*map)->map[y]) && direction_count <= 1)
		{
			if ((*map)->map[y][x] == 'N' || (*map)->map[y][x] == 'S'
				|| (*map)->map[y][x] == 'E' || (*map)->map[y][x] == 'W')
				direction_count++;
			x++;
		}
		y++;
	}
	if (direction_count != 1)
		print_error_and_exit("Only one spawn direction required");
}

void	first_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\r')
	{
		if (line[i] != '1' && line[i] != ' ')
			print_error_and_exit("No walls in top or bot");
		i++;
	}
}
