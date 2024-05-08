/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/08 14:51:39 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_texture(t_tex *art, void *mlx, char *path, const char err)
{
	art->img.img = mlx_xpm_file_to_image(mlx, path, &art->width, &art->height);
	if (!art->img.img)
		return (errmsg_errno_var(err, path), 1);
	art->img.pixel_ptr = mlx_get_data_addr(art->img.img, &art->img.bits_per_pixel,
		&art->img.line_length, &art->img.endian);
	if (!art->img.pixel_ptr)
		return (1);
	return (0);
}

static int	load_texture_wall(t_game *g)
{
	int		i;
	char	**path;

	i = -1;
	path = (char *[]){"art/floor.xpm", "art/floor.xpm", "art/floor.xpm", "art/floor.xpm"};
	while (++ i < 4)
	{
		if (g->wall[i].img.img)
			continue ;
		if (load_texture(&g->wall[i], g->mlx.mlx, path[i], -1))
			return (1);
	}
	return (0);
}

int	load_art_n_mlx(t_game *g)
{
	if (load_texture_wall(g))
		return (1);
	if (!g->env[0].set)
		g->env[0].colour.mode = (t_trbg){0, 255, 0, NO_TRANSPARENCY};
	if (!g->env[1].set)
		g->env[1].colour.mode = (t_trbg){255, 0, 0, NO_TRANSPARENCY};
	g->env[0].set = 1;
	g->env[1].set = 1;
	g->scene.img = mlx_new_image(g->mlx.mlx, MAX_WIDTH, MAX_HEIGTH);
	if (!g->scene.img)
		return (1); // cannot load image for scene
	g->scene.pixel_ptr = mlx_get_data_addr(g->scene.img, &g->scene.bits_per_pixel,
		&g->scene.line_length, &g->scene.endian);
	if (!g->scene.pixel_ptr)
		return (1); //cannot access image
	return (0);
}
