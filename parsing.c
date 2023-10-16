/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:33:50 by adgutier          #+#    #+#             */
/*   Updated: 2023/10/07 18:33:50 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	default_error(void)
{
	perror("\033[1;31mERROR\033[0m");
	exit(1);
}

char	**read_map(char *fmap)
{
	int		fd;
	char	*line;
	char	*joined_lines;

	line = "";
	joined_lines = ft_strdup("");
	fd = open(fmap, O_RDONLY);
	if (fd < 0)
		default_error();
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n')
			break ;
		joined_lines = ft_strjoin(joined_lines, line);
	}
	close(fd);
	if (joined_lines[0] == '\0')
		default_error();
	return (ft_split(joined_lines, '\n'));
}

void fill_dir(t_map *map)
{
    int y;
    int x;

    y = 0;
    while (y < map->y)
    {
        x = 0;
        while (x < map->x)
        {
            if (map->map[y][x] == 'N')
			{
				map->player->dir = 'N';
				map->player->vect_y = 1;
				map->player->vect_x = 0;
				map->player->x_pj = x;
				map->player->y_pj = y;
				return ;
			}
			else if (map->map[y][x] == 'S')
			{
				map->player->dir = 'S';
				map->player->vect_y = -1;
				map->player->vect_x = 0;
				map->player->x_pj = x;
				map->player->y_pj = y;
				return ;
			}
        	else if (map->map[y][x] == 'E')
			{
				map->player->dir = 'E';
				map->player->vect_y = 0;
				map->player->vect_x = 1;
				map->player->x_pj = x;
				map->player->y_pj = y;
				return ;
			}
			else if (map->map[y][x] == 'W')
			{
				map->player->dir = 'W';
				map->player->vect_y = 0;
				map->player->vect_x = -1;
				map->player->x_pj = x;
				map->player->y_pj = y;
				return ;
			}
            x++;
        }
        y++;
    }
}