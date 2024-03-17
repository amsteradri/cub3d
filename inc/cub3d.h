/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:15:34 by adgutier          #+#    #+#             */
/*   Updated: 2024/03/17 09:46:04 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define DR 0.0174533
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT_ARROW 65361
# define KEY_RIGHT_ARROW 65363
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

typedef struct s_line
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
}				t_line;

typedef struct s_player
{
	char		dir;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		x;
	double		y;
}				t_player;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			side;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	double		wall_x;
	int			col;
	double		fov;
	double		step;
	double		offset;
}				t_ray;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_draw
{
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_draw;

typedef struct s_map
{
	char		**map;
	char		no[256];
	char		so[256];
	char		we[256];
	char		ea[256];
	t_img		*no_img;
	t_img		*so_img;
	t_img		*we_img;
	t_img		*ea_img;
	t_img		*char_2d;
	t_img		*wall_2d;
	t_img		*back_2d;
	t_img		*door;
	int			fr;
	int			fg;
	int			fb;
	int			cr;
	int			cg;
	int			cb;
	int			x;
	int			y;
	int			screen_width;
	int			screen_height;
	t_player	*player;
	t_ray		*ray;
	void		*win_ptr;
	void		*mlx_ptr;
	t_img		*img;
	t_img		*texture;
	t_line		*line;
	t_draw		*draw;
}				t_map;

/* draw/ */
// calculations_draw.c //
void	calculate_tex_x(t_map *map, t_img *img);
void	calculate_draw_values(t_map *map);
void	calculate_wall_x(t_map *map);

// draw.c //
void	draw(t_map *map);
void	draw_ceil(t_map *map);
void	draw_floor(t_map *map);
void	get_wall_orientation(t_map *map, t_img **img);
void	draw_wall(t_map *map);

/* movements/ */
// movements.c //
void	move_forward(t_map *map);
void	move_backward(t_map *map);
void	move_right(t_map *map);
void	move_left(t_map *map);
int		move_character(int keycode, t_map *map);

// movements2.c //
int		is_valid_move(int fil, int col, t_map *map);
void	move_camera_left(t_map *map);
void	move_camera_right(t_map *map);

/* parse/ */
// colors_and_directions.c //
void	get_texture_path(char *line, char *direction);
void	get_color_parse(char *line, int *r, int *g, int *b);
void	parse_colors_and_directions(t_map *map);
int		find_first_map_row(t_map *map);

// errors.c //
void	error_args(int argc);
void	check_ext(char *map);
void	check_chars(t_map **map);
void	check_nsew(t_map **map);
void	first_line(char *line);

// errors2.c //
void	check_walls(t_map **map);
int		is_valid_character(char c);
void	check_surrounding(t_map **map, int i, int j, int aux);
void	check_under_empty(t_map **map);
void	all_checks(t_map *map);

// parse.c //
char	**read_map(char *fmap);
char	check_direction(t_map *map, int *x, int *y);
void	init_direction_values(t_map *map);

// parse2.c //
void	init_north_values(t_map *map);
void	init_south_values(t_map *map);
void	init_east_values(t_map *map);
void	init_west_values(t_map *map);

/* raycast/ */
// raycast.c //
void	initialize_ray(t_map *map);
void	calculate_delta_distance(t_map *map);
void	calculate_side_distance(t_map *map);
void	dda_algorithm(t_map *map);
int		raycast(t_map *map);

// raycast2.c
void	calculate_perpendicular_distance(t_map *map);

/* render/ */
// render.c //
void	render_walls_2d(t_map *map);
void	draw_diagonal_line(t_map *map, double x, double y);
void	render_char_2d(t_map *map);
int		render_all(t_map *map);

/* textures/ */
// textures.c //
void	load_texture(t_map *map, t_img *img, char *path);
void	initialize_textures(t_map *map);
void	texture_on_img(t_map *map, t_img *img);

/* utils/ */
// frees.c //
void	free_map(t_map *map);
void	free_all(t_map *map);

// inits.c //
void	init_vars_map(t_map *map);
void	init_vars_imgs(t_map *map);
void	init_vars_draw(t_map *map);
void	init_vars_ray(t_map *map);
void	init_vars_player(t_map *map);

// inits2.c //
void	init_vars_line(t_map *map);
void	init_vars_texture(t_map *map);
void	inits_structs(t_map *map);

// mlx.c //
void	my_img_pixel_put(t_map *map, int x, int y, int color);
void	pixel_on_img(t_map *map, int rgb, int x, int y);
void	mlx_hooks(t_map *map);
void	mlx_destroy_images(t_map *map);
void	mlx_functions(t_map *map);

// utils.c //
int		map_height(char **map);
int		find_longest_line_length(char **map);
int		create_rgb_color(int red, int green, int blue);
int		ft_spacelen(char *str);
void	print_error_and_exit(const char *message);

/* window/ */
// cub_window.c //
void	create_window(t_map *map);
void	create_img(t_map *map);
int		handle_esc_screen(t_map *map);

#endif