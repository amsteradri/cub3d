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
		if (line == NULL)
			break ;
		joined_lines = ft_strjoin(joined_lines, line);
	}
	close(fd);
	if (joined_lines[0] == '\0')
		default_error();
	return (ft_split(joined_lines, '\n'));
}

void	fill_dir(t_map *map)
{
	int		i;
	int		aux;
	int		j;
	int		len;

	i = 1;
	j = 0;
	aux = map->y - 1;
	len = ft_strlen(map->map[i]) - 1;
	while (i < aux)
	{
		j = 0;
		len = ft_strlen(map->map[i]) - 1;
		
		while(j < len)
		{
			if (map->map[i][j] == 'N')
			{
				map->player->dir = 'N';
				map->player->x = j + 1;
				map->player->y = i + 1;
				map->player->dir_x = 0;
				map->player->dir_y = -1;
				map->player->plane_x = 0.66;
				map->player->plane_y = 0;
				return ;
			}
			else if (map->map[i][j] == 'S')
			{
				map->player->dir = 'S';
				map->player->x = j + 1;
				map->player->y = i + 1;
				map->player->dir_x = 0;
				map->player->dir_y = 1;
				map->player->plane_x = -0.66;
				map->player->plane_y = 0;
				return ;
			}
        	else if (map->map[i][j] == 'E')
			{
				map->player->dir = 'E';
				map->player->x = j + 1;
				map->player->y = i + 1;
				map->player->dir_x = 1;
				map->player->dir_y = 0;
				map->player->plane_x = 0;
				map->player->plane_y = 0.66;
				return ;
			}
			else if (map->map[i][j] == 'W')
			{
				map->player->dir = 'W';
				map->player->x = j + 1;
				map->player->y = i + 1;
				map->player->dir_x = -1;
				map->player->dir_y = 0;
				map->player->plane_x = 0;
				map->player->plane_y = -0.66;
				return ;
			}
			j++;
		}
		i++;
	}
}