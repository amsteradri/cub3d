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
# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

#define DR 0.0174533 // Un grado en radianes
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT_ARROW 65361
#define KEY_RIGHT_ARROW 65363


typedef struct s_line_h
{
	double	intersection_x;
	double	intersection_y;
	double	xa;
	double	ya;
	double	perp_dist;
	double	correct_dist;
} 	t_line_h;

typedef struct s_line_v
{
	double	intersection_x;
	double	intersection_y;
	double	xa;
	double	ya;
	double	perp_dist;
	double	correct_dist;
}	t_line_v;

typedef struct	s_lines
{
	t_line_h	line_h;
	t_line_v	line_v;
}	t_lines;

typedef struct	s_player
{
	char			dir; // N, S, W, E
	double			x;
	double			y;
}	t_player;

typedef struct	s_ray
{
	double			x;
	double			y;
	double			angle_between_rays;
	double			angle;
	double			dist_player_projection_plane;
	int				current_col;
	double			dist_to_slice;
}	t_ray;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_img;

typedef struct s_map
{
	char			**map;
	char 			no[256];
    char 			so[256];
    char 			we[256];
    char 			ea[256];
	int				fr;
	int				fg;
	int				fb;
	int				cr;
	int				cg;
	int				cb;
	int				x;
	int				y;
	int				screen_width;
	int				screen_height;
	t_player		*player;
	t_ray			*ray;
	t_lines			*line;
	void			*win_ptr;
	void			*mlx_ptr;
	t_img			*img;
}	t_map;

// cub_window.c //
void	create_window(t_map *map);
int		handle_esc_screen(t_map *map);
void	create_img(t_map *map);

// cub3d.c //
int		map_height(char **map);
int		find_longest_line_length(char **map);
void	init_vars_map(t_map *map);

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

// parsemap.c //
void parse_top_map(t_map *map);
int find_first_map_row(t_map *map);

// ray_casting.c //
int		raycast(t_map *map);
int		find_vertical_intersection(t_map *map, double ray_x, double ray_y, double angle);
int		find_horizontal_intersection(t_map *map, double ray_x, double ray_y, double angle);

// render.c //
int		render_all(t_map *map);

// render2d.c //
void	render_background_2d(t_map *map);
void	render_empty_2d(t_map *map);
void	render_walls_2d(t_map *map);
void	render_char_2d(t_map *map);

// render3d.c //

#endif