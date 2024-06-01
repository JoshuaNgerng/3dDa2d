/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/30 13:31:20 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
init image in memory t_img from external vpm file
mlx ptr path_name of vpmfile, len of filename (for writting err purpose)
1 cant make img, 0 success
*/
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

/*
init empty image in memoery t_img
mlx ptr , width and height info
1 cant make img, 0 success
*/
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
	char	**path;

	i = -1;
	path = (char *[]){"art/wall_2.xpm",
		"art/wall_1.xpm", "art/wall_4.xpm", "art/bluestone.xpm"};
	while (++ i < 4)
	{
		if (g->wall[i].img)
			continue ;
		if (load_texture(&g->wall[i], g->mlx.mlx, path[i], ft_strlen(path[i])))
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
}

/*
main game struct
title for mlx windows
load every texture of the game if not set in the .cub file
load img in memory to write to before putting to win
*/
int	load_mlx_img(t_game *g, char *title)
{
	char	*path;

	g->mlx.win = mlx_new_window(g->mlx.mlx,
		g->setting.win_width,  g->setting.win_height, title);
	if (!g->mlx.win)
		return (errmsg_config_errno(1), 1);
	if (load_texture_wall(g))
		return (1);
	if (g->door.len > 0)
	{
		path = "art/eagle.xpm";
		if (load_texture(&g->door_img[0], g->mlx.mlx, path, ft_strlen(path)))
			return (1);
		path = "art/purplestone.xpm";
		if (load_texture(&g->door_img[1], g->mlx.mlx, path, ft_strlen(path)))
			return (1);
		g->door.max_index = g->door_img->height - 10;
	}
	if (!g->env[floor_].set)
		g->env[floor_].colour = (t_colour){.mode.green = 255};
	if (!g->env[sky_].set)
		g->env[sky_].colour = (t_colour){.mode.blue = 255};
	if (load_img(&g->scene, g->mlx.mlx,
		g->setting.win_width, g->setting.win_height))
		return (errmsg_config_errno(2), 1);
	if (load_img(&g->minimap, g->mlx.mlx,
		g->setting.minimap_width, g->setting.minimap_height))
		return (errmsg_config_errno(3), 1);
	set_minimap_info(&g->minimap_info, g);
	return (0);
}
