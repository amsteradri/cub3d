/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isromero <isromero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:15:34 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/19 21:41:26 by isromero         ###   ########.fr       */
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

# define DR 0.0174533 // Un grado en radianes
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
	int			y0;
	int			y1;
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
	int			len_to_wall; // para dibujar rayitos
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
	int			hit;
	double		wall_x;
	int			col;
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

// cub_window.c //
void			create_window(t_map *map);
int				handle_esc_screen(t_map *map);
void			create_img(t_map *map);

// cub3d.c //
int				map_height(char **map);
int				find_longest_line_length(char **map);
void			init_vars_map(t_map *map);

// movements.c //
int				move_character(int keycode, t_map *map);

// parsing_errors.c //
void			error_args(int argc);
void			check_ext(char *map);
void			check_chars(t_map **map);
void			check_nsew(t_map **map);
void			first_line(char *line);
int				ft_spacelen(char *str);
void			check_walls(t_map **map);
void			check_under_empty(t_map **map);
void			all_checks(t_map *map);

// parsing.c //
void			default_error(void);
char			**read_map(char *fmap);
void			fill_dir(t_map *map);

// textures.c //
void			load_texture(t_map *map, t_img *img, char *path);
void			draw_textures(t_map *map);
void			calculate_draw_values(t_map *map);
int				create_rgb_color(int red, int green, int blue);
void			texture_on_img(t_map *map, t_img *img);

// textures2.c //

void	draw_textures(t_map *map);

// parsemap.c //
void			parse_top_map(t_map *map);
int				find_first_map_row(t_map *map);

// ray_casting.c //
int				raycast(t_map *map);

// render.c //
int				render_all(t_map *map);

// render2d.c //
void	render_back_2d(t_map *map);
void			render_empty_2d(t_map *map);
void			render_walls_2d(t_map *map);
void			render_char_2d(t_map *map);

// render3d.c //

// utils.c //

#endif