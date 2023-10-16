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


typedef struct s_player
{
	char			dir;
	int				vect_x;
	int				vect_y;
	int				x_pj;
	int				y_pj;
}t_player;


typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
	t_player		*player;

	// void			*win_ptr;
	// void			*mlx_ptr;
}t_map;



//parsin_errors.c//

void	check_ext(char *map);
void	error_args(int argc);
void	check_chars(t_map **map);
void	all_checks(t_map *map);
void    check_nsew(t_map **map);
void	check_walls(t_map **map);
void	check_under_empty(t_map **map);

// parsing.c//
void	first_line(char *line);
char	**read_map(char *fmap);
void fill_dir(t_map *map);





#endif