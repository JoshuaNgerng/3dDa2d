/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:38:13 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/05 21:30:28 by jngerng          ###   ########.fr       */
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

# define MAX_WIDTH		1500
# define MAX_HEIGHT		1000
# define MAX_RENDER		7
# define MAX_RENDER_OBJ	6

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <errno.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"

typedef enum e_x_event
{
	key_press = 2,
	key_release = 3,
	mouse_press = 4,
	mouse_release = 5,
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
	ekey = 14,
	mkey = 46,
	lshift = 257,
	rshift = 258
}	t_key;

typedef enum e_side
{
	horizontal = 0,
	vertical = 1,
	north = 0,
	east = 2,
	south = 1,
	west = 3,
	floor_ = 0,
	sky_ = 1,
	wall = 0,
	door = 1,
	key = 2,
	door_end = 3,
	door_ = 4,
	undef = UCHAR_MAX
}	t_side;

typedef enum e_move
{
	forward = 1,
	backward = 1 << 1,
	move_left = 1 << 2,
	move_right = 1 << 3,
	rotate_left = 1 << 4,
	rotate_right = 1 << 5,
	interact_door = 1 << 6,
	map_option = 1 << 7
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
	int		len;
	t_list_	*list;
	t_list_	*tail;
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
	double	fov;
	double	depth_of_focus;
	t_point	pos;
	t_point	n_dir;
	t_point	p_dir;
	t_point	view;
	double	rotate_sin[2];
	double	rotate_cos[2];
}	t_ply;

typedef struct s_img
{
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*img;
	char	*pixel_ptr;
}	t_img;

typedef struct s_ray_fin
{
	uint8_t	side;
	uint8_t	type;
	int		index;
	int		height;
	double	perp_dist;
	double	hitpoint;
}	t_ray_fin;

typedef struct s_ray_comp
{
	int		map_check;
	int		step_dir;
	double	step_size;
	double	check_dist;
}	t_ray_comp;

typedef struct s_ray
{
	uint8_t		side;
	int			ray_no;
	int			obj_iter;
	t_point		ray_dir;
	t_ray_comp	hori;
	t_ray_comp	verti;
	t_ray_fin	fin[MAX_RENDER];
}	t_ray;

typedef struct s_draw
{
	int			height;
	int			win_height;
	t_int		screen_pos;
	t_int		texture_pos;
	t_img		*scene;
	const t_img	*texture;
}	t_draw;

typedef struct s_ani
{
	int8_t	status;
	int		counter;
	t_int	pos;
}	t_ani;

typedef struct t_asset
{
	int		len;
	int		max_index;
	t_ani	*sprite;
}	t_asset;

typedef struct s_set
{
	int	fov;
	int	move_speed;
	int	rotation_speed;
	int	win_width;
	int	win_height;
	int	minimap_width;
	int	minimap_height;
}	t_set;

typedef struct s_map
{
	int		width;
	int		height;
	char	*map;
}	t_map;

typedef struct s_mmap
{
	int			block_per_row;
	int			block_per_col;
	t_int		border_size;
	t_int		block_size;
	t_int		block_border_size;
	t_colour	empty;
	t_colour	door;
	t_colour	border;
	t_colour	black;
	t_colour	grey;
}	t_mmap;

typedef struct s_game
{
	t_map	map;
	t_mlx	mlx;
	t_ply	ply;
	t_set	setting;
	t_img	scene;
	t_img	minimap;
	t_mmap	minimap_info;
	t_env	env[2];
	t_img	wall[4];
	t_img	door_img[2];
	t_asset	door;
}	t_game;

/* error messages */

void		errmsg_prog(char type);
void		errmsg_file_errno(char type, const char *s);
void		errmsg_prog_errno(const char *msg, size_t len);
void		errmsg_config(char type);
void		errmsg_config_var(char type, const char *msg, size_t len);
void		errmsg_config_errno(char type);
void		errmsg_img(const char *msg, size_t len);

/* utilites */

int			skip_char(const char *s, char c, int i);
int			skip_till_end(const char *s, const char *ref, int start);
char		*skip_empty_line(int fd, char *prev);
int			checkset(char c, const char *s);
int			strlcpy_over(char *dst, const char *src);
void		free_game(t_game *g);
int			free_exit(t_game *g, int ext_code);
int			check_line_end(const char *line, int index, \
	void (*f)(char ), char errtype);

/* math check */

int			get_map_pos(t_int p, const t_map *m);

/* read from file */

int			read_file(t_game *g, const char *file);
int			read_elements(int fd, t_game *g, char **ptr);
int			set_ply_pos(int col, char dir, t_ply *p);
int			check_map(char *line, int *ptr, t_game *g);
int			init_buffer_list(t_buffer *buffer, char *line, t_game *g);
int			cont_buffer_list(t_buffer *buffer, int fd, t_game *g);
int			uniform_map_size(t_game *g);
int			check_map_vertical(const t_map *m, t_asset *d);
void		free_buffer(t_buffer *b);

/* load mlx and texture */

int			load_texture(t_img *art, void *mlx, char *path, size_t str_len);
int			load_mlx_img(t_game *g, char *title);

/* make image  */

void		change_image_pixel(t_img *img, int x, int y, uint32_t colour);
uint32_t	get_image_pixel(const t_img *img, int x, int y);
void		generate_scene(t_game *g);
int			raycast_check(t_ray *r, const t_game *g);
void		raycasting_walls(t_img *img, const t_game *g);

/* mini map */

void		draw_horizontal(t_img *img, t_int range, int row, t_colour c);
void		draw_small_circle(t_img *minimap, const t_game *g);
void		draw_pointer(t_img *minimap, const t_game *g);
int			create_minimap(t_img *minimap, t_mlx *mlx, const t_game *g);
void		empty_minimap_init(t_img *minimap, const t_game *g);
void		refresh_minimap(t_img *minimap, const t_game *g);
int			get_map_pos(t_int p, const t_map *m);

/* game loop */

int			set_ply_mov(int key, t_game *g);
int			unset_ply_mov(int key, t_game *g);
int			mouse_set_ply(int key, int pos_x, int pos_y, t_game *g);
int			mouse_unset_ply(int key, int pos_x, int pos_y, t_game *g);
int			update_ply_move(t_ply *p, const t_game *g);
int			update_interact(t_asset *door, const t_game *g);
int			main_loop(t_game *g);

/* draw */

void		draw_init(t_ray_fin *obj, t_draw *d, const t_ray *r, \
	const t_game *g);
void		draw_flip_init(t_ray_fin *obj, t_draw *d, const t_ray *r, \
	const t_game *g);
void		draw_obj_to_img(t_img *img, t_ray *r, const t_game *g);
void		draw_obj_n_bg(t_img *img, t_ray *r, const t_game *g);
void		draw_obj(t_img *img, t_ray *r, const t_game *g);
void		drawing_loop(t_draw *d, const t_ray_fin *obj, int offset);
void		drawing_celling_loop(t_draw *d, t_ray_fin *back);
void		draw_sky(t_draw *draw, const t_game *g);
void		draw_floor(t_draw *draw, const t_game *g);

/* asset */

void		add_asset(t_asset *a, t_int pos);
int			get_asset_index(const t_asset *a, t_int pos);

/* door */

void		update_door(const t_map *m, const t_ply *ply, t_asset *door);
void		update_door_counter(t_asset *door);
int			get_door_stat(const t_asset *door, t_int pos, int *index_ptr);

void		print_map(const t_map *m);
int			test_minimap(int keycode, t_game *g);

#endif
