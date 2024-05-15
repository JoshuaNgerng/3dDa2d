/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:38:13 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/15 22:52:24 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE3D_H
# define CUBE3D_H
# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define BOLDCYAN	"\033[1m\033[36m"
# define BOLDYELLOW	"\033[1m\033[33m"
# define BOLDGREEN	"\033[1m\033[32m"
# define BOLDBLUE	"\033[1m\033[34m"
# define BOLDRED	"\033[1m\033[31m"

# define MAX_WIDTH	1500
# define MAX_HEIGHT	1000

# define NO_TRANSPARENCY		0
# define TRANSPARENCY_MINIMAP	125
# define WALL_MINIMAP "./art/wall_minimap.xpm"
# define WALL_SIZE_MINIMAP 32
# define PLAYER_MINIMAP "./art/player_minimap.xpm"
# define VIEW_MINIMAP "./art/view_minimap.xpm"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <errno.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include <limits.h>

typedef enum e_x_event
{
	key_press = 2,
	key_release = 3,
	mouse_press = 5,
	mouse_release = 6,
	esc_key = 17
}	t_x_event;

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

typedef enum e_side
{
	horizontal = 0,
	vertical = 1,
	north = 0,
	east = 1,
	south = 2,
	west = 3,
	floor_ = 0,
	sky_ = 1
}	t_side;

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

typedef struct s_int
{
	int	x;
	int	y;
}	t_int;

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
	double	depth_of_focus;
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

typedef struct s_ray_comp
{
	int		map_check;
	int		step_dir;
	double	step_size;
	double	check_dist;
}	t_ray_comp;

typedef struct s_ray
{
	int			side;
	double		perp_dist;
	double		hitpoint;
	t_point		ray_dir;
	t_ray_comp	hori;
	t_ray_comp	verti;
}	t_ray;

typedef struct s_set
{
	int	fov;
	int	move_speed;
	int	rotation_speed;
	int	win_width;
	int	win_height;
}	t_set;

typedef struct s_map
{
	int		width;
	int		height;
	char	*map;
	int		img_width;
	int		img_height;
	char	*mini_wall;
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

void	errmsg_prog(char type);
void	errmsg_file_errno(char type, const char *s);
void	errmsg_prog_errno(const char *msg, size_t len);
void	errmsg_config(char type);
void	errmsg_config_var(char type, const char *msg, size_t len);
void	errmsg_config_errno(char type);
void	errmsg_img(const char *msg, size_t len);


/* utilites */

int 	skip_char(const char *s, char *set, int i);
int		skip_till_end(const char *s, const char *ref, int start);
int		checkset(char c, const char *s);
int		strlcpy_over(char *dst, const char *src);
void	free_game(t_game *g);
int		free_exit(t_game *g, int ext_code);

/* math check */

int		get_map_pos(const t_point *p, const t_map *m);
void	rotation_matrix(t_point *dst, double sin_, double cos_);

/* read from file */

int		read_file(t_game *g, const char *file);
int		read_elements(int fd, t_game *g, char **ptr);
int		check_map(char *line, int *ptr, t_ply *p);
int		init_buffer_list(t_buffer *buffer, char *line, t_ply *p, int *ptr_width);
int		cont_buffer_list(t_buffer *buffer, int fd, int *, t_ply *p);
int		uniform_map_size(t_game *g);
int		check_map_vertical(const t_map *m);
void	free_buffer(t_buffer *b);
int		create_minimap(t_game *g);
int		create_minimap(t_game *g);

/* load mlx and texture */

int		load_texture(t_tex *art, void *mlx, char *path, size_t str_len);
int		load_mlx_img(t_game *g, char *title);

/* make image  */

void	change_image_pixel(t_img *img, int x, int y, uint32_t colour);
uint32_t	get_image_pixel(const t_tex *tex, int x, int y);
void	generate_scene(t_game *g);
int		raycast_loop(t_ray *r, int ray_no, const t_game *g);
void	raycasting_walls(t_img *img, const t_game *g);
// int		calculate_wall(t_ray_fin *fin, t_ray_fin *h, t_ray_fin *v, double angle);
// void	draw_wall(t_game *g, const t_ray_dist *r, int ray_no, double angle);

/* game loop */

int		set_ply_mov(int key, t_game *g);
int		unset_ply_mov(int key, t_game *g);
int		mouse_set_ply(int key, double pos_x, double pos_y, t_game *g);
int		mouse_unset_ply(int key, double pos_x, double pos_y, t_game *g);
int		update_ply_move(t_ply *p, const t_game *g);
int		animation(t_game *g);

void	print_map(const t_map *m);

#endif