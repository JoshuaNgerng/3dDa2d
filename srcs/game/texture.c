/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 10:21:44 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_texture(t_tex *art, void *mlx, char *path, size_t str_len)
{
	art->img.img = mlx_xpm_file_to_image(mlx, path, &art->width, &art->height);
	if (!art->img.img)
		return (errmsg_img(path, str_len), 1);
	art->img.pixel_ptr = mlx_get_data_addr(art->img.img,
			&art->img.bits_per_pixel, &art->img.line_length, &art->img.endian);
	if (!art->img.pixel_ptr)
		return (errmsg_img(path, str_len), 1);
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
		if (g->wall[i].img.img)
			continue ;
		if (load_texture(&g->wall[i], g->mlx.mlx, path[i], ft_strlen(path[i])))
			return (1);
	}
	return (0);
}

int	load_mlx_img(t_game *g, char *title)
{
	g->mlx.win = mlx_new_window(g->mlx.mlx, MAX_WIDTH, MAX_HEIGHT, title);
	if (!g->mlx.win)
		return (errmsg_config_errno(1), 1);
	if (load_texture_wall(g))
		return (1);
	if (!g->env[0].set)
		g->env[0].colour.mode = (t_trbg){0, 255, 0, NO_TRANSPARENCY};
	if (!g->env[1].set)
		g->env[1].colour.mode = (t_trbg){255, 0, 0, NO_TRANSPARENCY};
	g->env[0].set = 1;
	g->env[1].set = 1;
	g->scene.img = mlx_new_image(g->mlx.mlx, MAX_WIDTH, MAX_HEIGHT);
	if (!g->scene.img)
		return (errmsg_config_errno(2), 1);
	g->scene.pixel_ptr = mlx_get_data_addr(g->scene.img,
			&g->scene.bits_per_pixel, &g->scene.line_length, &g->scene.endian);
	if (!g->scene.pixel_ptr)
		return (errmsg_config_errno(2), 1);
	return (0);
}
