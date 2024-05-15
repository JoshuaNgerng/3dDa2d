/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:03:50 by lchew             #+#    #+#             */
/*   Updated: 2024/05/15 23:16:53 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_minimap(t_game *g)
{
	int		row;
	int		col;

	
	void	*ply;
	void	*view;
	int		i;
	int		j;
	
	ply = mlx_xpm_file_to_image(g->mlx.mlx, PLAYER_MINIMAP, &g->map.img_width, \
		&g->map.img_height);
	view = mlx_xpm_file_to_image(g->mlx.mlx, VIEW_MINIMAP, &g->map.img_width, \
		&g->map.img_height);
	g->map.mini_wall = mlx_xpm_file_to_image(g->mlx.mlx, WALL_MINIMAP,
			&g->map.img_width, &g->map.img_height);
	
	row = 0;
	i = (int)g->ply.pos.x - 3;
	int		minimap[7][7];

	while (row < 7)
	{
		col = 0;
		j = (int)g->ply.pos.y - 3;
		while (col < 7)
		{
			if (i >= 0 && j >= 0 && j < g->map.width && i < g->map.height)
				minimap[row][col] = g->map.map[i * g->map.width + j];
			else
				minimap[row][col] = ' ';
			++col;
			++j;
		}
		++row;
		++i;
	}
	double	tmpx;
	double	tmpy;
	
	tmpx = 3.5 * WALL_SIZE_MINIMAP;
	tmpy = 3.5 * WALL_SIZE_MINIMAP;
	double m;
	
	printf("g->ply.n_dir.x: %f ", g->ply.n_dir.x);
	printf("g->ply.n_dir.y: %f\n", g->ply.n_dir.y);
	if (g->ply.n_dir.x == -1)
		m = 3 * M_PI / 2;
	else if (g->ply.n_dir.x == 1)
		m = M_PI / 2;
	else
		m = atan2(g->ply.n_dir.x, g->ply.n_dir.y);
	printf("m: %f\n", m);
	
	int count = 30;
	
	while (count > 0)
	{
		tmpx += cos(m);
		tmpy += sin(m);
		change_image_pixel(&g->scene, (int)(tmpx), (int)(tmpy), (t_colour){.mode.red = 255}.trbg);
		--count;
	}
	// change_image_pixel(&g->scene, (int)(tmpx + 1), (int)(tmpy + m), (t_colour){.mode.red = 255}.trbg);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->scene.img, 0, 0);
	tmpx = 3.5 * WALL_SIZE_MINIMAP;
	tmpy = 3.5 * WALL_SIZE_MINIMAP;
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, ply, tmpy, tmpx);
	// mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, view, tmpy, tmpx - 1 * WALL_SIZE_MINIMAP);

	
	row = 0;
	while (row < 7)
	{
		col = 0;
		while (col < 7)
		{
			if (minimap[row][col] == '1')
				mlx_put_image_to_window(g->mlx.mlx, g->mlx.win,
					g->map.mini_wall, col * WALL_SIZE_MINIMAP, row * WALL_SIZE_MINIMAP);
			++col;
		}
		++row;
	}
	
	return (0);
}
