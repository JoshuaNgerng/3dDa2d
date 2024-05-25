/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:18:18 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/25 17:06:55 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_game(t_game *g)
{
	int	i;

	if (g->map.map)
		free(g->map.map);
	if (!g->mlx.mlx)
	{
		if (g->door.sprite)
			free(g->door.sprite);
		if (g->key.sprite)
			free(g->key.sprite);
		return ;
	}
	i = -1;
	while (++ i < 4)
	{
		if (g->wall[i].img)
			mlx_destroy_image(g->mlx.mlx, g->wall[i].img);
	}
	if (g->door.len > 0)
	{
		if (g->door_img.img)
			mlx_destroy_image(g->mlx.mlx, g->door_img.img);
		if (g->door.sprite)
			free(g->door.sprite);
	}
	if (g->key.len > 0)
	{
		if (g->key_img->img)
			mlx_destroy_image(g->mlx.mlx, g->key_img->img);
		if (g->key.sprite)
			free(g->key.sprite);
	}
	if (g->scene.img)
		mlx_destroy_image(g->mlx.mlx, g->scene.img);
	if (g->minimap.img)
		mlx_destroy_image(g->mlx.mlx, g->minimap.img);
	if (g->mlx.win)
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
	system("leaks cub3D");
	// if (g->mlx.mlx)
	// {
		// mlx_destroy_display(g->mlx.mlx);
		// free(g->mlx.mlx);
	// }
	// system("leaks cub3D");
}

int	free_exit(t_game *g, int ext_code)
{
	free_game(g);
	exit(ext_code);
	return (0);
}

void	print_map(const t_map *m)
{
	printf("height (%d) width (%d)\n", m->height, m->width);
	for (int i = 0; i < m->height; i ++)
	{
		for (int j = 0; j < m->width; j ++)
			printf("%c", m->map[i * m->width + j]);
		printf("\n");
	}
}
