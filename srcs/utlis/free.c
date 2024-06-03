/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:18:18 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 17:57:56 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	destroy(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (g->wall[i].img)
			mlx_destroy_image(g->mlx.mlx, g->wall[i].img);
	}
	if (g->door_img[0].img)
		mlx_destroy_image(g->mlx.mlx, g->door_img[0].img);
	if (g->door_img[1].img)
		mlx_destroy_image(g->mlx.mlx, g->door_img[1].img);
	if (g->scene.img)
		mlx_destroy_image(g->mlx.mlx, g->scene.img);
	if (g->minimap.img)
		mlx_destroy_image(g->mlx.mlx, g->minimap.img);
	if (g->mlx.win)
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
}

void	free_game(t_game *g)
{
	if (g->map.map)
		free(g->map.map);
	if (g->door.sprite)
		free(g->door.sprite);
	if (!g->mlx.mlx)
		return ;
	destroy(g);
}

int	free_exit(t_game *g, int ext_code)
{
	free_game(g);
	exit(ext_code);
	return (0);
}
