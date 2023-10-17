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
#include <math.h>



typedef struct s_player
{
	char			dir;
	int				vect_x;
	int				vect_y;
	int				j_pj;
	int				i_pj;
	int				len_to_wall;
}t_player;


typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
	t_player		*player;
	void			*win_ptr;
	void			*mlx_ptr;
}t_map;



void	create_window(t_map *map);

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

// cub_window.c //
void	init_window(t_map *map);
void draw_background(t_map *map);
void	create_window(t_map *map);




#endif