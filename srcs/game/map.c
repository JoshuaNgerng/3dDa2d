/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:03:50 by lchew             #+#    #+#             */
/*   Updated: 2024/05/20 17:08:17 by jngerng          ###   ########.fr       */
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

void	put_block_in_img(t_img *minimap, t_int pos, t_colour colour, const t_game *g)
{
	t_int	iter;
	t_int	minimap_img_pos;

	minimap_img_pos.x = pos.x * g->minimap_info.block_width + g->minimap_info.padding_x;
	iter.x = -1;
	// printf("pos x(%d) pos y (%d)\n", pos.x, pos.y);
	while (++ iter.x < g->minimap_info.block_width)
	{
		iter.y = -1;
		minimap_img_pos.y = pos.y * g->minimap_info.block_height + g->minimap_info.padding_y;
		while (++ iter.y < g->minimap_info.block_height)
		{
			// printf("minimap_img index (x)%d (y)%d\n", minimap_img_pos.x, minimap_img_pos.y);
			change_image_pixel(minimap, minimap_img_pos.x, minimap_img_pos.y, colour.trbg);
			minimap_img_pos.y ++;
		}
		minimap_img_pos.x ++;
	}
	
}

void	padd_empty(t_img *minimap, t_int pos, t_colour colour, const t_game *g)
{
	while (pos.x < g->minimap_info.block_per_row)
	{
		while (pos.y < g->minimap_info.block_per_col)
		{
			put_block_in_img(minimap, pos, colour, g);
			pos.y ++;
		}
		pos.x ++;
	}
}

void	put_player_on_map(t_img *minimap, const t_ply *p)
{
	// draw circle at ply pos
	// draw two lines at the edge of the vision
	// fill in all empty spaces in minimap
	(void)minimap;
	(void)p;
}

int	create_minimap(t_img *minimap, t_mlx *mlx, const t_game *g)
{
	int		map_char;
	t_int	iter;
	t_int	ref_pos;

	iter.x = -1;
	refresh_minimap(minimap, g);
	printf("ply pos %d %d \n", (int)g->ply.pos.x, (int)g->ply.pos.y);
	printf("g->minimap_info.block_per_col %d, g->minimap_info.block_per_row %d\n", g->minimap_info.block_per_col, g->minimap_info.block_per_row);
	printf("half %d %d\n", g->minimap_info.block_per_col / 2, g->minimap_info.block_per_row / 2);
	ref_pos.y = (int)g->ply.pos.y - g->minimap_info.block_per_row / 2;
	while (++ iter.x < g->minimap_info.block_per_row - 1)
	{
		ref_pos.x = (int)g->ply.pos.x - g->minimap_info.block_per_col / 2;
		iter.y = -1;
		while (++ iter.y < g->minimap_info.block_per_col - 1)
		{
			// printf("ref_pos (%d) (%d)\n", ref_pos.x, ref_pos.y);
			map_char = get_map_pos(ref_pos, &g->map);
			// printf("map char %d row(%d)col(%d)\n", map_char, ref_pos.x, ref_pos.y);
			if (ref_pos.x == (int)g->ply.pos.x && ref_pos.y == (int)g->ply.pos.y)
				put_block_in_img(minimap, iter, (t_colour){.mode.red = 255, .mode.green = 255}, g);
			else if (map_char == '0')
				put_block_in_img(minimap, iter, g->minimap_info.block_colour[0], g);
			else if (map_char == '1')
			{
				printf("iter x:%d y:%d, ref_pos x:%d, y:%d\n", iter.x, iter.y, ref_pos.x, ref_pos.y);
				put_block_in_img(minimap, iter, g->minimap_info.block_colour[2], g);
			}
			else if (map_char == 'D')
				put_block_in_img(minimap, iter, g->minimap_info.block_colour[3], g);
			else if (map_char == 'K')
				put_block_in_img(minimap, iter, g->minimap_info.block_colour[4], g);
			ref_pos.x ++;
		}
		ref_pos.y ++;
	}
	// put_player_on_map(minimap, &g->ply);
	return (mlx_put_image_to_window(mlx->mlx, mlx->win, minimap->img, 0, 0));
}
