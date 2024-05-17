/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:03:50 by lchew             #+#    #+#             */
/*   Updated: 2024/05/17 16:48:36 by jngerng          ###   ########.fr       */
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

void	padd_empty()
{
	;
}

void	add_block()
{
	;
}

int	create_minimap(t_img *minimap, const t_game *g)
{
	int		map_char;
	t_int	iter;
	t_int	ref_pos;

	(void)minimap;
	iter.x = -1;
	while (++ iter.x < 7)
	{
		ref_pos.x = g->ply.pos.x - 3;
		iter.y = -1;
		while (++ iter.y < 7)
		{
			map_char = get_map_pos(ref_pos, &g->map);
			if (map_char < 0)
				padd_empty();
			else if (map_char == ' ')
				;
			else if (map_char == '1')
				;
			else if (map_char == '0')
				;
			else if (map_char == 'D')
				;
			else if (map_char == 'K')
				;
		}
	}
	return (0);
}
