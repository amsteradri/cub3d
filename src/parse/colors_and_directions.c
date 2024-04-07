/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_and_directions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:15 by adgutier          #+#    #+#             */
/*   Updated: 2024/04/07 12:03:19 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_path(char *line, char *direction)
{
	int	j;
	int	k;

	j = 3;
	k = 0;
	if (line == NULL || (int)ft_strlen(line) <= j)
	{
		ft_strcpy(direction, "assets/default.xpm");
		return ;
	}
	while (line[j] != '\0' && line[j] != '\n' && line[j] != ' '
		&& line[j] != '\t' && line[j] != '\r')
		direction[k++] = line[j++];
	direction[k] = '\0';
}

void	get_color_parse(char *line, int *r, int *g, int *b)
{
	int	j;

	j = 2;
	if (line == NULL || (int)ft_strlen(line) <= j)
	{
		*r = 0;
		*g = 0;
		*b = 0;
		return ;
	}
	*r = ft_atoi(&line[j]);
	while (line[j] != ',' && line[j])
		j++;
	if (line[j] == ',')
		j++;
	*g = ft_atoi(&line[j]);
	while (line[j] != ',' && line[j])
		j++;
	if (line[j] == ',')
		j++;
	*b = ft_atoi(&line[j]);
}

void	parse_colors_and_directions(t_map *map)
{
	int	i;

	i = 0;
	map->no[0] = '\0';
	map->we[0] = '\0';
	map->so[0] = '\0';
	map->ea[0] = '\0';
	while (map->map[i] != NULL)
	{
		if (ft_strncmp(map->map[i], "NO", 2) == 0)
			get_texture_path(map->map[i], map->no);
		else if (ft_strncmp(map->map[i], "SO", 2) == 0)
			get_texture_path(map->map[i], map->so);
		else if (ft_strncmp(map->map[i], "WE", 2) == 0)
			get_texture_path(map->map[i], map->we);
		else if (ft_strncmp(map->map[i], "EA", 2) == 0)
			get_texture_path(map->map[i], map->ea);
		else if (ft_strncmp(map->map[i], "F", 1) == 0)
			get_color_parse(map->map[i], &map->fr, &map->fg, &map->fb);
		else if (ft_strncmp(map->map[i], "C", 1) == 0)
			get_color_parse(map->map[i], &map->cr, &map->cg, &map->cb);
		i++;
	}
}

int	find_first_map_row(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		if (map->map[i][0] == ' ')
		{
			j = 0;
			while (map->map[i][j] && (map->map[i][j] != '1'
					&& map->map[i][j] != '0'))
				j++;
			if (map->map[i][j] == '1' || map->map[i][j] == '0')
				return (i);
		}
		else if (map->map[i][0] == '1' || map->map[i][0] == '0')
			return (i);
		i++;
	}
	return (0);
}
