/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:38:13 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/28 15:37:10 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define RESET		"\033[0m"
# define BOLDCYAN	"\033[1m\033[36m"
# define BOLDYELLOW	"\033[1m\033[33m"
# define BOLDGREEN	"\033[1m\033[32m"
# define BOLDBLUE	"\033[1m\033[34m"
# define BOLDRED	"\033[1m\033[31m"
# define MAX_WIDTH	2000
# define MAX_HEIGTH	1000
# define HEIGHT_LIM	800
# define DEGREE		0.01745329251
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define ROTATION_SPEED	DEGREE * 5
# define MOVE_SPEED		0.5
# define DEPTH_OF_FOCUS	8
# define CHECK_DIST		10
# define FOV			120
# define RAY_FREQ		120
# define RAY_UNIT_DIST	0.5
# define NO_TRANSPARENCY	0
# define TRANSPARENCY_MINIMAP	125
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <errno.h>
# include <stdint.h>
# include <string.h>
# include "mlx.h"
# include "libft.h"

# include <stdio.h>

# ifndef M_PI
#  define M_PI		3.14159265358979323846	/* pi */
# endif
# ifndef M_PI_2
#  define M_PI_2	1.57079632679489661923	/* pi/2 */
# endif
# ifndef M_PI_4
#  define M_PI_4	0.78539816339744830962	/* pi/4 */
# endif
# ifndef M_1_PI
#  define M_1_PI	0.31830988618379067154	/* 1/pi */
# endif
#define _2_M_PI		6.28318530717958647692	/* 2 pi */

typedef enum e_key
{
	esc = 53,
	up = 126,
	left = 123,
	right = 124,
	down = 125,
	wkey = 13,
	akey = 0,
	skey = 1,
	dkey = 2,
	qkey = 12,
	ekey = 14
}	t_key;

typedef enum e_move
{
	forward = 1,
	backward = 1 << 1,
	move_left = 1 << 2,
	move_right = 1 << 3,
	rotate_left = 1 << 4,
	rotate_right = 1 << 5
}	t_move;

typedef struct s_trbg
{
	uint8_t	blue;
	uint8_t	green;
	uint8_t	red;
	uint8_t	transparency;
}	t_trbg;

typedef union colour
{
	t_trbg		mode;
	uint8_t		trabg_parts[4];
	uint32_t	trbg;
}	t_colour;

typedef struct s_list_
{
	char			*line;
	struct s_list_	*next;
}	t_list_;

typedef struct s_buffer
{
	int		len; // how many rows in map
	t_list_	*list; // head 
	t_list_	*tail; // tail for adding
}	t_buffer;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_env
{
	char		set;
	t_colour	colour;
}	t_env;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_ply
{
	char	move_options;
	double	move_speed;
	double	fov; // .66 or 1.0
	t_point	pos;
	t_point	n_dir; // dir 
	t_point	p_dir; // x_dir
	t_point	view;
	double	rotate_sin[2];
	double	rotate_cos[2];
}	t_ply;

typedef struct	s_img
{
	void	*img;
	char	*pixel_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_tex
{
	int		width;
	int		height;
	t_img	img;
}	t_tex;

typedef struct s_ray_dist
{
	char	type;
	double	ray_x;
	double	ray_y;
	double	x_offset;
	double	y_offset;
	double	dist;
}	t_ray_dist;

typedef struct s_ray
{
	int		no_ray;
	int		dof;
	double	angle;
	double	start_x;
	double	start_y;
	double	tan;
}	t_ray;

typedef struct s_ray_fin
{
	double	ray_x;
	double	ray_y;
	double	dist;
}	t_ray_fin;

typedef struct s_set
{
	int		wall_strip_width;
	int		depth_of_focus;
	double	ray_freq;
	double	angle_delta;
	double	angle_start;
}	t_set;

typedef struct s_map
{
	int		width;
	int		heigth;
	int		unit_size;
	char	*map;
}	t_map;

typedef struct s_game
{
	t_map	map;
	t_mlx	mlx;
	t_ply	ply;
	t_set	setting;
	t_img	scene;
	t_env	env[2]; //FC
	t_tex	wall[4]; //NESW
}	t_game;

/* error messages */

void	errmsg(char type);
void	errmsg_var(char type, const char *msg);
void	errmsg_errno_var(char type, const char *msg);

/* utilites */

int		skip_char(const char *s, char *set, int start);
int		checkset(char c, const char *s);
int		strlcpy_over(char *dst, const char *src);
void	free_game(t_game *g);
int		free_exit(t_game *g, int ext_code);

/* math check */

double	get_distance(double	ax, double ay, double bx, double by);
double	new_angle(double *ptr, double new_angle);
int		get_map_pos(const t_point *p, const t_map *m);
void	rotation_matrix(t_point *dst, double sin_, double cos_);

/* read from file */

int		read_file(t_game *g, const char *file);
int		read_elements(int fd, t_game *g, char **ptr);
int		check_map(char *line, int *ptr, t_ply *p);
int		init_buffer_list(t_buffer *buffer, char *line, t_ply *p);
int		cont_buffer_list(t_buffer *buffer, int fd, int *, t_ply *p);
int		uniform_map_size(t_game *g);
int		check_map_vertical(const t_map *m);
void	free_buffer(t_buffer *b);

/* load mlx and texture */

int		load_texture(t_tex *art, void *mlx, char *path, const char err);
int		load_art_n_mlx(t_game *g);

/* make image  */

void	change_image_pixel(t_img *img, int x, int y, unsigned int colour);
void	generate_scene(t_game *g);
void	raycasting_walls(t_img *img, const t_game *g);
int		calculate_wall(t_ray_fin *fin, t_ray_fin *h, t_ray_fin *v, double angle);
void	draw_wall(t_game *g, const t_ray_dist *r, int ray_no, double angle);

/* game loop */

int		handle_input(int key, t_game *g);
int		set_ply_mov(int key, t_game *g);
int		unset_ply_mov(int key, t_game *g);
int		update_ply_move(t_ply *p, const t_game *g);
int		animation(t_game *g);

void	print_map(const t_map *m);

#endif