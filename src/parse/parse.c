/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:33:50 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/24 16:49:47 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_map(char *fmap)
{
	int		fd;
	char	*line;
	char	*joined_lines;

	line = "";
	joined_lines = ft_strdup("");
	fd = open(fmap, O_RDONLY);
	if (fd < 0)
		print_error_and_exit("");
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		joined_lines = ft_strjoin(joined_lines, line);
	}
	close(fd);
	if (joined_lines[0] == '\0')
		print_error_and_exit("");
	return (ft_split(joined_lines, '\n'));
}

char	check_direction(t_map *map, int *x, int *y)
{
	char	direction[5];
	int		i;
	int		j;
	char	*found;

	ft_strcpy(direction, "NSWE");
	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (direction[j])
		{
			found = strchr(map->map[i], direction[j]);
			if (found != NULL)
			{
				*x = found - map->map[i];
				*y = i;
				return (direction[j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_direction_values(t_map *map)
{
	int	x;
	int	y;

	if (check_direction(map, &x, &y) == 'N')
		init_north_values(map);
	else if (check_direction(map, &x, &y) == 'S')
		init_south_values(map);
	else if (check_direction(map, &x, &y) == 'E')
		init_east_values(map);
	else if (check_direction(map, &x, &y) == 'W')
		init_west_values(map);
	map->player->x = x + 0.5;
	map->player->y = y + 0.5;
}
