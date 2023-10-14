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