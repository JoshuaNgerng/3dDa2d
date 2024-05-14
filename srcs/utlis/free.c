/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:18:18 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 13:03:50 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_game(t_game *g)
{
	int	i;

	free(g->map.map);
	if (!g->mlx.mlx)
		return ;
	i = -1;
	while (++ i < 4)
	{
		if (g->wall[i].img.img)
			mlx_destroy_image(g->mlx.mlx, g->wall[i].img.img);
	}
	if (g->scene.img)
		mlx_destroy_image(g->mlx.mlx, g->scene.img);
	if (g->mlx.win)
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
	// system("leaks cub3D");
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

// void	print_map(const t_map *m)
// {
// 	printf("height (%d) width (%d)\n", m->height, m->width);
// 	for (int i = 0; i < m->height; i ++)
// 	{
// 		for (int j = 0; j < m->width; j ++)
// 			printf("%c", m->map[i * m->width + j]);
// 		printf("\n");
// 	}
// }
