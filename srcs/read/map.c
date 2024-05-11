/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:03:50 by lchew             #+#    #+#             */
/*   Updated: 2024/05/11 14:38:14 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_minimap(t_game *g)
{
	int		row;
	int		col;

	printf("Creating minimap\n");
	row = 0;
	g->map.mini_wall = mlx_xpm_file_to_image(g->mlx.mlx, WALL_MINIMAP,
			&g->map.img_width, &g->map.img_height);
	while (row < g->map.height)
	{
		col = 0;
		while (col < g->map.width && g->map.map[row * g->map.width + col] != '\0')
		{
			if (g->map.map[row * g->map.width + col] == '1')
				mlx_put_image_to_window(g->mlx.mlx, g->mlx.win,
					g->map.mini_wall, col * WALL_SIZE_MINIMAP, row * WALL_SIZE_MINIMAP);
			++col;
		}
		++row;
	}
	return (0);
}
