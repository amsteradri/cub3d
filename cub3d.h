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
# include <math.h>

#define ROTATION_ANGLE 10 // Valor de la velocidad de rotación en radianes por frame (se suma/se resta ángulo)

typedef struct s_player
{
	char			dir;
	int				vect_x;
	int				vect_y;
	int				j_pj;
	int				i_pj;
	int				len_to_wall;
	double			camera_angle;
	double			rotation_angle;
}	t_player;

typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
	t_player		*player;
	void			*win_ptr;
	void			*mlx_ptr;
}	t_map;

// cub_window.c //
void	create_window(t_map *map);
void	draw_background(t_map *map);
void	print_empty_on_map(t_map *map);
void	print_obstacles_on_map(t_map *map);
void	print_char_on_map(t_map *map);
void	render_all(t_map *map);
void	init_window(t_map *map);

// cub3d.c //
int		map_height(char **map);
int		find_longest_line_length(char **map);
void	init_vars(t_map *map);

// movements.c //
int		is_valid_move(int fil, int col, t_map *map);
int		move_character(int keycode, t_map *map);

// parsing_errors.c //
void	error_args(int argc);
void	check_ext(char *map);
void	check_chars(t_map **map);
void    check_nsew(t_map **map);
void	first_line(char *line);
int		ft_spacelen(char *str);
void	check_walls(t_map **map);
void	check_under_empty(t_map **map);
void	all_checks(t_map *map);

// parsing.c //
void	default_error(void);
char	**read_map(char *fmap);
void	fill_dir(t_map *map);

// ray_casting.c //
void	draw_ray(t_map *map, int j, int i);
void	draw_diagonal_line(t_map *map, double angle, int i, int j);

#endif