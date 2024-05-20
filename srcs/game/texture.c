/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/20 16:13:19 by jngerng          ###   ########.fr       */
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
	m->block_height = 10;
	m->block_width = 10;
	m->padding_x = 5;
	m->padding_y = 5;
	m->block_per_row = (g->setting.minimap_width - m->padding_x) / m->block_width;
	m->block_per_col = (g->setting.minimap_height - m->padding_y) / m->block_height;\
	m->block_colour[0] = (t_colour){.mode.transparency = 125, .mode.red = 128, .mode.blue = 128, .mode.green = 128};
	m->block_colour[1] = (t_colour){.mode.transparency = 125, .mode.red = 100, .mode.blue = 50, .mode.green = 50};
	m->block_colour[2] = (t_colour){.mode.transparency = 125};
	m->block_colour[3] = (t_colour){.mode.transparency = 125, .mode.green = 128};
	m->block_colour[4] = (t_colour){.mode.transparency = 125, .mode.blue = 100};
}

int	load_mlx_img(t_game *g, char *title)
{
	char	*path;

	g->mlx.win = mlx_new_window(g->mlx.mlx, MAX_WIDTH, MAX_HEIGHT, title);
	if (!g->mlx.win)
		return (errmsg_config_errno(1), 1);
	if (load_texture_wall(g))
		return (1);
	if (g->door.len > 0)
	{
		path = "art/purplestone.xpm";
		if (load_texture(&g->door_img, g->mlx.mlx, path, ft_strlen(path)))
			return (1);
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
	printf("minimap width(%d), height(%d), block width(%d) height (%d), block_per (%d) (%d)\n", g->minimap.width, g->minimap.height, g->minimap_info.block_width, g->minimap_info.block_height, g->minimap_info.block_per_row, g->minimap_info.block_per_col);
	return (0);
}
