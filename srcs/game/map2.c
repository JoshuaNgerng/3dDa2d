/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:11:49 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/24 22:39:59 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	empty_minimap_init(t_img *minimap, const t_game *g)
{
	int			row;
	t_colour	border;

	row = -1;
	border = (t_colour){.mode.transparency = 100, .mode.red = 200};
	while (++ row < g->minimap_info.border_size.x)
		draw_horizontal(minimap, (t_int){0, g->minimap.height}, row, border);
	while (row < g->minimap.width - g->minimap_info.border_size.x)
	{
		draw_horizontal(minimap,
			(t_int){0, g->minimap_info.border_size.y}, row, border);
		draw_horizontal(minimap,
			(t_int){g->minimap.height - g->minimap_info.border_size.y + 1,
			g->minimap.height}, row, border);
		row ++;
	}
	while (row < g->minimap.width)
	{
		draw_horizontal(minimap, (t_int){0, g->minimap.height}, row, border);
		row ++;
	}
}

void	refresh_minimap(t_img *minimap, const t_game *g)
{
	int	row;

	row = g->minimap_info.border_size.x;
	while (++ row < g->minimap.width - g->minimap_info.border_size.x)
		draw_horizontal(minimap,
			(t_int){g->minimap_info.border_size.y + 1,
			g->minimap.height - g->minimap_info.border_size.y},
			row, g->minimap_info.empty);
}
