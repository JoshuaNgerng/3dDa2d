/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/15 17:08:34 by jngerng          ###   ########.fr       */
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
	char	**path;

	i = -1; // N S W E
	path = (char *[]){"art/floor.xpm",
		"art/wall_1.xpm", "art/eagle.xpm", "art/bluestone.xpm"};
	while (++ i < 4)
	{
		if (g->wall[i].img)
			continue ;
		if (load_texture(&g->wall[i], g->mlx.mlx, path[i], ft_strlen(path[i])))
			return (1);
	}
	return (0);
}

static int	load_texture_key(t_game *g)
{
	int		i;
	char	**path;

	i = -1; // N S W E
	path = (char *[]){"art/floor.xpm",
		"art/wall_1.xpm", "art/eagle.xpm", "art/bluestone.xpm"};
	while (++ i < 4)
	{
		if (g->key_img[i].img)
			continue ;
		if (load_texture(&g->key_img[i], g->mlx.mlx, path[i], ft_strlen(path[i])))
			return (1);
	}
	return (0);
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
		if (load_texture(&g->door.texture, g->mlx.mlx, path, ft_strlen(path)))
			return (1);
	}
	if (!g->env[0].set)
		g->env[0].colour.mode = (t_trbg){0, 255, 0, NO_TRANSPARENCY};
	if (!g->env[1].set)
		g->env[1].colour.mode = (t_trbg){255, 0, 0, NO_TRANSPARENCY};
	if (load_img(&g->scene, g->mlx.mlx, MAX_WIDTH, MAX_HEIGHT))
		return (errmsg_config_errno(2), 1);
	if (load_img(&g->mini_map, g->mlx.mlx, 20, 20))
		return (errmsg_config_errno(3), 1);
	return (0);
}
