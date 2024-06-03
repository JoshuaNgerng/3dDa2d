/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:11:49 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 09:53:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Colour the minimap borders.
 *
 * This function fills the minimap borders with a specified colour. It takes
 * the minimap image and the game information as parameters. The colour of the
 * borders is defined by the `border` variable. The function iterates through
 * the rows of the minimap and draws horizontal lines to colour the borders.
 *
 * @param minimap The minimap image.
 * @param g The game information.
 */
void	empty_minimap_init(t_img *minimap, const t_game *g)
{
	int			row;
	t_colour	border;

	row = -1;
	border = (t_colour){.mode.transparency = 100, .mode.red = 200};
	while (++row < g->minimap_info.border_size.x)
		draw_horizontal(minimap, (t_int){0, g->minimap.height}, row, border);
	while (row < g->minimap.width - g->minimap_info.border_size.x)
	{
		draw_horizontal(minimap,
			(t_int){0, g->minimap_info.border_size.y}, row, border);
		draw_horizontal(minimap,
			(t_int){g->minimap.height - g->minimap_info.border_size.y + 1,
			g->minimap.height}, row, border);
		row++;
	}
	while (row < g->minimap.width)
	{
		draw_horizontal(minimap, (t_int){0, g->minimap.height}, row, border);
		row++;
	}
}

/**
 * @brief Fill the minimap with empty color, excluding the borders.
 *
 * This function fills the minimap with an empty color, excluding the borders.
 * It takes the minimap image and the game information as parameters. The empty
 * color is defined by the `empty` variable in the game information. The function
 * iterates through the rows of the minimap, starting from the row after the top
 * border and ending at the row before the bottom border. It then calls the
 * `draw_horizontal` function to draw a horizontal line with the empty color.
 *
 * @param minimap The minimap image.
 * @param g The game information.
 */
void	refresh_minimap(t_img *minimap, const t_game *g)
{
	int	row;

	row = g->minimap_info.border_size.x + 1;
	while (row < g->minimap.width - g->minimap_info.border_size.x)
	{
		draw_horizontal(minimap,
			(t_int){g->minimap_info.border_size.y + 1,
			g->minimap.height - g->minimap_info.border_size.y},
			row, g->minimap_info.empty);
		row++;
	}
}
