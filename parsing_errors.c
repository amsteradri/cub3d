/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:25:52 by adgutier          #+#    #+#             */
/*   Updated: 2023/10/07 18:25:52 by adgutier         ###   ########.fr       */
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
	if (map[len - 4] != '.' && map[len - 4] != 'c'
		&& map[len - 4] != 'u' && map[len - 4] != 'b')
	{
        perror("\033[1;31mERROR: Wrong map extension\033[0m");
        exit(0);
    }
}

void	all_checks(t_map *map)
{
	check_chars(&map);
    check_nsew(&map);
	check_walls(&map);
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
				&& (*map)->map[y][x] != 'S' && (*map)->map[y][x] != 'W' && (*map)->map[y][x] != ' ')
				{
                    perror("\033[1;31mERROR: Wrong map components\033[0m");
                    exit(0);
                }
			x++;
		}
		y++;
	}
}

void check_nsew(t_map **map)
{
    int y;
    int x;
    int direction_count = 0;

    y = 0;
    while (y < (*map)->y && direction_count <= 1)
    {
        x = 0;
        while (x < (*map)->x && direction_count <= 1)
        {
            if ((*map)->map[y][x] == 'N' || (*map)->map[y][x] == 'S' ||
                (*map)->map[y][x] == 'E' || (*map)->map[y][x] == 'W')
            {
                direction_count++;
            }
            x++;
        }
        y++;
    }
    if (direction_count != 1)
    {
		perror("\033[1;31mERROR: Only one spawn direction requiered\033[0m");
        exit(0);
	}
}

void	first_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0' && line[i] != '\r')
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			perror("\033[1;31mERROR: No walls in top or bot\033[0m");
            exit(0);
		}
	}
}

int ft_spacelen(char *str) 
{
    int l;
    int count;
    int i;

	i = l - 1;
    l = strlen(str);
	count = 0;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\r')) 
	{
        count++;
        i--;
    }

    return count;
}


void	check_walls(t_map **map)
{
	int		i;
	int		aux;
	int		j;

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
			perror("\033[1;31mERROR: No walls in first col\033[0m");
            exit(0);
		}
		if ((*map)->map[i][ft_strlen((*map)->map[i]) - ft_spacelen((*map)->map[i]) - 1] != '1')
		{
			printf("mi char:%d\n", (*map)->map[i][ft_strlen((*map)->map[i]) - ft_spacelen((*map)->map[i]) - 1]);
			perror("\033[1;31mERROR: No walls in last col\033[0m");
            exit(0);
		}
		i++;
	}
	first_line((*map)->map[(*map)->y - 1]);
}
