/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/11 17:24:38 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3d.h"

int	get_map_pos(const t_point *p, const t_map *m)
{
	if (p->x < 0 || p->y < 0)
		return (-1);
	if (p->y > m->width || p->x > m->height)
		return (-1);
	return (m->map[(int)p->x * m->width + (int)p->y]);
}

void	rotation_matrix(t_point *dst, double sin_, double cos_)
{
	t_point	buffer;

	buffer = (t_point){.x = dst->x, .y = dst->y};
	dst->x = (buffer.x * cos_) - (buffer.y * sin_);
	dst->y = (buffer.x * sin_) + (buffer.y * cos_);
}
