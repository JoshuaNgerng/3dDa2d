/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/24 22:40:10 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_texture(t_img *art, void *mlx, char *path, size_t str_len)
{
	art->img = mlx_xpm_file_to_image(mlx, path, &art->width, &art->height);
	if (!art->img)
		return (errmsg_img(path, str_len), 1);
	art->pixel_ptr = mlx_get_data_addr(art->img, &art->bits_per_pixel,
			&art->line_length, &art->endian);
	if (!art->pixel_ptr)
		return (errmsg_img(path, str_len), 1);
	return (0);
}

static int	load_img(t_img *i, void *mlx, int width, int height)
{
	i->width = width;
	i->height = height;
	i->img = mlx_new_image(mlx, width, height);
	if (!i->img)
		return (1);
	i->pixel_ptr = mlx_get_data_addr(i->img,
			&i->bits_per_pixel, &i->line_length, &i->endian);
	if (!i->pixel_ptr)
		return (1);
	return (0);
}

static int	load_texture_wall(t_game *g)
{
	int		i;
	int		*len;
	char	**path;

	i = -1; // N S W E
	path = (char *[]){"art/floor.xpm",
		"art/wall_1.xpm", "art/eagle.xpm", "art/bluestone.xpm"};
	len = (int []){13, 14, 13, 17};
	while (++ i < 4)
	{
		if (g->wall[i].img)
			continue ;
		if (load_texture(&g->wall[i], g->mlx.mlx, path[i], len[i]))
			return (1);
	}
	return (0);
}

static int	load_texture_key(t_game *g)
{
	int		i;
	int		*len;
	char	**path;

	i = -1;
	if (g->key.len <= 0)
		return (0);
	path = (char *[]){"art/floor.xpm",
		"art/wall_1.xpm", "art/eagle.xpm", "art/bluestone.xpm"};
	len = (int []){13, 14, 13, 17};
	while (++ i < 4)
	{
		if (g->key_img[i].img)
			continue ;
		if (load_texture(&g->key_img[i], g->mlx.mlx, path[i], len[i]))
			return (1);
	}
	return (0);
}

void	set_minimap_info(t_mmap *m, const t_game *g)
{
	m->block_size.y = 15;
	m->block_size.x = 15;
	m->border_size.x = 5;
	m->border_size.y = 5;
	m->block_border_size.x = 2;
	m->block_border_size.y = 2;
	m->block_per_row = (g->setting.minimap_width - m->border_size.x)
		/ m->block_size.x;
	m->block_per_col = (g->setting.minimap_height - m->border_size.y)
		/ m->block_size.y;
	m->grey = (t_colour){.mode.transparency = 150,
		.mode.red = 128, .mode.blue = 128, .mode.green = 128};
	m->empty = (t_colour){.mode.transparency = 175,
		.mode.red = 100, .mode.blue = 50, .mode.green = 50};
	m->black = (t_colour){.mode.transparency = 128};
	m->door = (t_colour){.mode.transparency = 128, .mode.green = 128};
	m->key = (t_colour){.mode.transparency = 128, .mode.blue = 100};
}

int	load_mlx_img(t_game *g, char *title)
{
	char	*path;

	g->mlx.win = mlx_new_window(g->mlx.mlx, g->setting.win_width,  g->setting.win_height, title);
	if (!g->mlx.win)
		return (errmsg_config_errno(1), 1);
	if (load_texture_wall(g))
		return (1);
	if (g->door.len > 0)
	{
		path = "art/purplestone.xpm";
		if (load_texture(&g->door_img, g->mlx.mlx, path, ft_strlen(path)))
			return (1);
		int	i = -1;
		g->door.max_index = g->door_img.height - 10;
		while (++ i < g->door.len)
			g->door.sprite[i].counter = g->door.max_index;
		printf("door img data width %d height %d\n", g->door_img.width, g->door_img.height);
	}
	if (load_texture_key(g))
		return (1);
	if (!g->env[floor_].set)
		g->env[floor_].colour = (t_colour){.mode.green = 255};
	if (!g->env[sky_].set)
		g->env[sky_].colour = (t_colour){.mode.blue = 255};
	if (load_img(&g->scene, g->mlx.mlx, g->setting.win_width, g->setting.win_height))
		return (errmsg_config_errno(2), 1);
	if (load_img(&g->minimap, g->mlx.mlx, g->setting.minimap_width, g->setting.minimap_height))
		return (errmsg_config_errno(3), 1);
	set_minimap_info(&g->minimap_info, g);
	// printf("minimap width(%d), height(%d), block width(%d) height (%d), block_per (%d) (%d)\n", g->minimap.width, g->minimap.height, g->minimap_info.block_size.y, g->minimap_info.block_size.x, g->minimap_info.block_per_row, g->minimap_info.block_per_col);
	return (0);
}
