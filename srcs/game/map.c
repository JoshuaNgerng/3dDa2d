/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:03:50 by lchew             #+#    #+#             */
/*   Updated: 2024/05/15 14:24:47 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_map_pos(t_int p, const t_map *m)
{
	if (p.x < 0 || p.y < 0)
		return (-1);
	if (p.y > m->width || p.x > m->height)
		return (-1);
	return (m->map[p.x * m->width + p.y]);
}

int	create_minimap(t_game *g)
{
	int	row;
	int	col;

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
