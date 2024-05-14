/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:21:04 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 17:29:35 by jngerng          ###   ########.fr       */
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

void	rotation_matrix(t_point *dst, double sin_, double cos_)
{
	t_point	buffer;

	buffer = (t_point){.x = dst->x, .y = dst->y};
	dst->x = (buffer.x * cos_) - (buffer.y * sin_);
	dst->y = (buffer.x * sin_) + (buffer.y * cos_);
}

int	update_move(t_point *ply, const t_point *move, const t_game *g, int dir)
{
	int		update;
	t_point	check;

	update = 0;
	check = (t_point){ply->x, ply->y};
	check.x += dir * move->x * g->ply.move_speed;
	if (get_map_pos((t_int){(int)check.x, (int)check.y}, &g->map) == '0')
	{
		*ply = (t_point){check.x, check.y};
		update = 1;
	}
	check = (t_point){ply->x, ply->y};
	check.y += dir * move->y * g->ply.move_speed;
	if (get_map_pos((t_int){(int)check.x, (int)check.y}, &g->map) == '0')
	{
		*ply = (t_point){check.x, check.y};
		update = 1;
	}
	return (update);
}

int	update_angle(t_ply *p, int dir)
{
	rotation_matrix(&p->n_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->p_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->view, p->rotate_sin[dir], p->rotate_cos[dir]);
	return (1);
}

int	update_ply_move(t_ply *p, t_door *d, const t_game *g)
{
	int	update;

	update = 0;
	if (p->move_options & rotate_left)
		update = update_angle(p, 0);
	else if (p->move_options & rotate_right)
		update = update_angle(p, 1);
	if (p->move_options & move_left)
		update = update_move(&p->pos, &p->p_dir, g, 1);
	else if (p->move_options & move_right)
		update = update_move(&p->pos, &p->p_dir, g, -1);
	if (p->move_options & forward)
		update = update_move(&p->pos, &p->n_dir, g, 1);
	else if (p->move_options & backward)
		update = update_move(&p->pos, &p->n_dir, g, -1);
	return (update);
}
