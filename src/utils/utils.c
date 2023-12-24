/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:02:38 by isromero          #+#    #+#             */
/*   Updated: 2023/12/24 13:34:23 by isromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

int	find_longest_line_length(char **map)
{
	int	longest_length;
	int	current_length;

	longest_length = 0;
	if (map == NULL)
	{
		return (longest_length);
	}
	for (int i = 0; map[i] != NULL; i++)
	{
		current_length = strlen(map[i]);
		if (current_length > longest_length)
			longest_length = current_length;
	}
	return (longest_length);
}

int	create_rgb_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	ft_spacelen(char *str)
{
	int	l;
	int	count;
	int	i;

	l = ft_strlen(str);
	i = l - 1;
	count = 0;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\r'))
	{
		count++;
		i--;
	}
	return (count);
}

void	default_error(void)
{
	perror("\033[1;31mERROR\033[0m");
	exit(1);
}
