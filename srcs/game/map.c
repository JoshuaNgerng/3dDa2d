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

/**
 * @brief Reads a character from a given position in the map.
 *
 * This function reads a character from a given position in the map. The position
 * is specified by the `p` parameter, and the map is specified by the `m` 
 * parameter.
 *
 * If the specified position is out of bounds (either less than 0 or greater than
 * or equal to the map's width or height), the function returns -1 to indicate an
 * error.
 *
 * Otherwise, the function calculates the index of the position in the map's 
 * character array by multiplying the x coordinate by the map's width and adding 
 * the y coordinate. It then returns the character at this index in the map's 
 * character array.
 * 
 * @param p The position in the map to read from.
 * @param m The map structure.
 * @return The character from the map at the given position, or -1 if the 
 * position is out of bounds.
 */
int	get_map_pos(t_int p, const t_map *m)
{
	if (p.x < 0 || p.y < 0)
		return (-1);
	if (p.y >= m->width || p.x >= m->height)
		return (-1);
	return (m->map[p.x * m->width + p.y]);
}

/**
 * @brief Draws a block with a given color in the minimap image.
 *
 * This function draws a block with a given color in the minimap image. The 
 * position of the block is specified by the `pos` parameter, and the color of 
 * the block is specified by the `colour` parameter. The minimap image and the 
 * game structure are specified by the `minimap` and `g` parameters, 
 * respectively.
 *
 * The function calculates the starting row and ending row of the block based on 
 * the position and the size of the block in the minimap. It then iterates over 
 * each row and calls the `draw_horizontal` function to draw a horizontal line 
 * with the specified color in the minimap image.
 * 
 * @param minimap The minimap image.
 * @param pos The position of the block in the minimap.
 * @param colour The color of the block.
 * @param g The game structure.
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

/**
 * @brief Put the player on the minimap.
 *
 * This function draws a small circle at the player's position and two lines at
 * the edge of the player's vision on the minimap. It also fills in all the
 * empty spaces on the minimap.
 *
 * @param minimap The minimap image.
 * @param g The game structure containing player information.
 */
void	put_player_on_map(t_img *minimap, const t_game *g)
{
	draw_small_circle(minimap, g);
	draw_pointer(minimap, g);
}

/**
 * @brief Checks the minimap for valid characters and draws blocks accordingly.
 *
 * This function checks the minimap for valid characters at the given reference
 * position and draws blocks in the minimap image based on the characters found.
 * The reference position is specified by the `ref_pos` parameter, and the 
 * position on the minimap to draw is specified by the `iter` parameter. The 
 * minimap image and the game structure are specified by the `minimap` and `g` 
 * parameters, respectively.
 *
 * The function retrieves the character at the reference position from the map
 * using the `get_map_pos` function. If the character is less than 0, indicating
 * an error, the function returns without drawing anything.
 *
 * The function calls the `put_block_in_img` function to draw a block in the
 * minimap image at the specified position based on the character found in the
 * map.
 *
 * @param ref_pos The reference position to check in the map.
 * @param iter The position on the minimap to draw.
 * @param minimap The minimap image.
 * @param g The game structure.
 */
void	check_minimap(t_int ref_pos, t_int iter, t_img *minimap, \
	const t_game *g)
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

/**
 * @brief Draws the minimap in memory and puts it on the window.
 *
 * This function creates a minimap image in memory and draws the blocks 
 * representing the map on it. It then puts the minimap image on the right 
 * bottom corner of the window.
 *
 * The function starts by refreshing the minimap img using the `refresh_minimap`
 * function. It then iterates over each block in the minimap and calls the 
 * `check_minimap` function to draw the corresponding block on the minimap image.
 * The position of the block in the minimap is calculated based on the player's 
 * position and the size of the minimap. The `put_player_on_map` function is also
 * called to draw the player's position on the minimap.
 *
 * Finally, the function puts the minimap image on the window using the 
 * `mlx_put_image_to_window` function.
 *
 * @param minimap The minimap image.
 * @param mlx The mlx structure.
 * @param g The game structure.
 * @return The result of the `mlx_put_image_to_window` function.
 */
int	create_minimap(t_img *minimap, t_mlx *mlx, const t_game *g)
{
	t_int	iter;
	t_int	ref_pos;

	iter.x = -1;
	refresh_minimap(minimap, g);
	ref_pos.y = (int)g->ply.pos.y - g->minimap_info.block_per_row / 2;
	while (++iter.x < g->minimap_info.block_per_row - 1)
	{
		ref_pos.x = (int)g->ply.pos.x - g->minimap_info.block_per_col / 2;
		iter.y = -1;
		while (++iter.y < g->minimap_info.block_per_col - 1)
		{
			check_minimap(ref_pos, iter, minimap, g);
			ref_pos.x++;
		}
		ref_pos.y++;
	}
	put_player_on_map(minimap, g);
	return (mlx_put_image_to_window(mlx->mlx, mlx->win, minimap->img,
			g->scene.width - minimap->width,
			g->scene.height - minimap->height));
}
