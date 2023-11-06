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

typedef	struct	s_line
{
	int x;
	int y;
	int y0;
	int y1;
	int tex_x;
	int	tex_y;
	double wall_x;
}	t_line;

/* 
	@param x La coordenada x de la línea relativa a la pantalla
	@param y La coordenada y de la línea relativa a la pantalla
	@param y0 La coordenada y del punto inicial de donde tiene que empezar a pintar la textura
	@param y1 La coordenada y del punto final de donde tiene que terminar de pintar la textura
	@param tex_x La coordenada x de la textura
	@param tex_y La coordenada y de la textura
	@param wall_x La posición exacta de la pared donde se ha impactado el rayo
 */

typedef struct	s_ray
{
	int				pos_x;
	int				pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}	t_ray;

/* 
	@param pos_x La posición x del jugador
	@param pos_y La posición y del jugador
	@param dir_x La dirección del vector x del jugador
	@param dir_y La dirección del vector y del jugador
	@param plane_x La dirección del plano x del jugador
	@param plane_y La dirección del plano y del jugador
	@param camera_x La posición x de la cámara (líneas vertícales de la pantalla)
	@param ray_dir_x La dirección del vector x del rayo
	@param ray_dir_y La dirección del vector y del rayo
	@param map_x La posición x que ha avanzado el jugador en el mapa
	@param map_y La posición y que ha avanzado el jugador en el mapa
	@param side_dist_x La distancia recorrida que hay dentro de un bloque en el eje x
	@param side_dist_y La distancia recorrida que hay dentro de un bloque en el eje y
	@param delta_dist_x La distancia que queda por recorrer en un bloque hasta el otro bloque en el eje x
	@param delta_dist_y La distancia que queda por recorrer en un bloque hasta el otro bloque en el eje y
	@param perp_wall_dist La distancia perpendicular a la pared(desde el jugador hasta el muro)
	@param step_x El paso que tiene que dar el jugador en el eje x
	@param step_y El paso que tiene que dar el jugador en el eje y
	@param hit Si el rayo ha impactado con un muro
	@param side Si el rayo ha impactado con un muro NS o EW
 */

typedef struct	s_player
{
	char			dir; // N, S, W, E
	int				vect_x; //dirX
	int				vect_y; //dirY
	int				j_pj; // posX
	int				i_pj; // posY
	int				len_to_wall;
	double			camera_angle;
	double			rotation_angle;
	int				move_up;
	int				move_left;
	int				move_right;
	int				move_down;
	int				move_camera_left;
	int				move_camera_right;
}	t_player;

typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
	int				screen_width;
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
void	render_all(t_map *map, t_ray *ray, t_line *line);
int		handle_esc_screen(t_map *map);
void	init_window(t_map *map, t_ray *ray, t_line *line);

// cub3d.c //
int		map_height(char **map);
int		find_longest_line_length(char **map);
void	init_vars_map(t_map *map);
void	init_vars_ray(t_ray *ray, t_map *map);

// movements.c //
int		is_valid_move(int fil, int col, t_map *map);
int		move_character(int keycode, t_map *map, t_ray *ray, t_line *line);
int		handle_key_press(int keycode, t_map *map);
int		handle_key_release(int keycode, t_map *map);

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
int		raycast_implementation(t_map *map, t_ray *ray, t_line *line);

#endif