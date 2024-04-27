/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:11:35 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/22 19:04:54 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	get_distance(double	ax, double ay, double bx, double by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}

double	new_angle(double *ptr, double new_angle)
{
	if (new_angle < 0)
		new_angle += _2_M_PI;
	else if (new_angle >= _2_M_PI)
		new_angle -= _2_M_PI;
	if (ptr)
		*ptr = new_angle;
	return (new_angle);
}

int	get_map_pos(const t_point *p, const t_map *m)
{
	if (p->x < 0 || p->y < 0)
		return (-1);
	if (p->x > m->heigth || p->y > m->width)
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