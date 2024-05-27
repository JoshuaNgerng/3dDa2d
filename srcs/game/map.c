/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:03:50 by lchew             #+#    #+#             */
/*   Updated: 2024/05/27 09:58:01 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
get read a given pos from map
if invalid pos (out of bound) return -1
char from map (as int ) otherwise
*/
int	get_map_pos(t_int p, const t_map *m)
{
	if (p.x < 0 || p.y < 0)
		return (-1);
	if (p.y >= m->width || p.x >= m->height)
		return (-1);
	return (m->map[p.x * m->width + p.y]);
}

/*
draw a block with a given colour row by row
*/
void	put_block_in_img(t_img *minimap, t_int pos,
	t_colour colour, const t_game *g)
{
	int		row;
	int		row_end;
	t_int	range;

	row = pos.x * g->minimap_info.block_size.x
		+ g->minimap_info.border_size.x;
	row_end = row + g->minimap_info.block_size.x;
	range.x = pos.y * g->minimap_info.block_size.y
		+ g->minimap_info.border_size.y;
	range.y = range.x + g->minimap_info.block_size.y;
	while (row < row_end)
	{
		draw_horizontal(minimap, range, row, colour);
		row ++;
	}
}

void	put_player_on_map(t_img *minimap, const t_game *g)
{
	// draw circle at ply pos
	// draw two lines at the edge of the vision
	// fill in all empty spaces in minimap
	draw_small_circle(minimap, g);
}
/*
ref_pos, the pos being checked
iter, pos on the minimap to draw

draw a block if valid char from map
ignore otherwise
*/
void	check_minimap(t_int ref_pos, t_int iter, t_img *minimap, const t_game *g)
{
	int	map_char;

	map_char = get_map_pos(ref_pos, &g->map);
	if (map_char < 0)
		return ;
	if (map_char == '0')
		put_block_in_img(minimap, iter, g->minimap_info.grey, g);
	else if (map_char == '1')
		put_block_in_img(minimap, iter, g->minimap_info.black, g);
	else if (map_char == 'D')
		put_block_in_img(minimap, iter, g->minimap_info.door, g);
}

/*
draw minimap in t_img memory
then put on the right bottom corner of the window from mlx img in memory
*/
int	create_minimap(t_img *minimap, t_mlx *mlx, const t_game *g)
{
	t_int	iter;
	t_int	ref_pos;

	iter.x = -1;
	refresh_minimap(minimap, g);
	ref_pos.y = (int)g->ply.pos.y - g->minimap_info.block_per_row / 2;
	while (++ iter.x < g->minimap_info.block_per_row - 1)
	{
		ref_pos.x = (int)g->ply.pos.x - g->minimap_info.block_per_col / 2;
		iter.y = -1;
		while (++ iter.y < g->minimap_info.block_per_col - 1)
		{
			check_minimap(ref_pos, iter, minimap, g);
			ref_pos.x ++;
		}
		ref_pos.y ++;
	}
	put_player_on_map(minimap, g);
	return (mlx_put_image_to_window(mlx->mlx,mlx->win, minimap->img,
		g->scene.width - minimap->width, g->scene.height - minimap->height));
}

/*
int	test_minimap(int keycode, t_game *g)
{
	int			map_char;
	static int	set = 0;
	static int	iter_x;
	static int	iter_y;
	static int	ref_pos_x;
	static int	ref_pos_y;

	if (keycode == esc)
		free_exit(g, 0);
	mlx_clear_window(g->mlx.mlx, g->mlx.win);
	// printf("ref_pos (%d) (%d)\n", ref_pos_x, ref_pos_y);
	if (!set)
	{
		ref_pos_x = (int)g->ply.pos.x - g->minimap_info.block_per_col / 2;
		ref_pos_y = (int)g->ply.pos.y - g->minimap_info.block_per_row / 2;
		set = 1;
	}
	map_char = get_map_pos((t_int){ref_pos_x, ref_pos_y}, &g->map);
	// printf("1map char %d row(%d)col(%d)\n", map_char, ref_pos_x, ref_pos_y);
	if (ref_pos_x == (int)g->ply.pos.x && ref_pos_y == (int)g->ply.pos.y)
		put_block_in_img(&g->minimap, (t_int){iter_x, iter_y}, (t_colour){.mode.red = 255, .mode.green = 255}, g);
	else if (map_char == '0')
		put_block_in_img(&g->minimap, (t_int){iter_x, iter_y}, g->minimap_info.grey, g);
	else if (map_char == '1')
		put_block_in_img(&g->minimap, (t_int){iter_x, iter_y}, g->minimap_info.black, g);
	else if (map_char == 'D')
		put_block_in_img(&g->minimap, (t_int){iter_x, iter_y}, g->minimap_info.door, g);
	else if (map_char == 'K')
		put_block_in_img(&g->minimap, (t_int){iter_x, iter_y}, g->minimap_info.key, g);
	iter_y ++;
	ref_pos_x ++;
	// printf("2map char %d row(%d)col(%d)\n", map_char, ref_pos_x, ref_pos_y);
	if (iter_y == g->minimap_info.block_per_col - 1 && iter_x != g->minimap_info.block_per_row - 1)
	{
		iter_x ++;
		iter_y = 0;
		ref_pos_y ++;
		ref_pos_x = (int)g->ply.pos.x - g->minimap_info.block_per_col / 2;
	}
	if (iter_x == g->minimap_info.block_per_row - 1 && iter_y == g->minimap_info.block_per_row - 1)
	{
		refresh_minimap(&g->minimap, g);
		iter_x = 0;
		iter_y = 0;
		ref_pos_y = (int)g->ply.pos.y - g->minimap_info.block_per_row / 2;
		ref_pos_x = (int)g->ply.pos.x - g->minimap_info.block_per_col / 2;
	}
	// printf("3map char %d row(%d)col(%d)\n", map_char, ref_pos_x, ref_pos_y);
	return (mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->minimap.img, 0, 0));
}
*/