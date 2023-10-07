/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:15:34 by adgutier          #+#    #+#             */
/*   Updated: 2023/10/07 18:15:34 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <mlx.h>

typedef struct t_map
{
	char			**map;
	int				x;
	int				y;
	// void			*win_ptr;
	// void			*mlx_ptr;
}t_map;

//parsin_errors.c//

void	check_ext(char *map);
void	error_args(int argc);
void	check_chars(t_map **map);
void	all_checks(t_map *map);
void    check_nsew(t_map **map);

// parsing.c//
char	**read_map(char *fmap);





#endif