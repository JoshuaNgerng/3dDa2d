/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:21:04 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 11:41:34 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	update_move(t_point *ply, const t_point *move, const t_game *g, int dir)
{
	int		update;
	t_int	check;
	t_point	buffer;

	update = 0;
	buffer = (t_point){ply->x, ply->y};
	buffer.x += dir * move->x * g->ply.move_speed;
	check = (t_int){(int)buffer.x, (int)buffer.y};
	if (get_map_pos(check, &g->map) == '0')
	{
		*ply = (t_point){buffer.x, buffer.y};
		update = 1;
	}
	buffer = (t_point){ply->x, ply->y};
	buffer.y += dir * move->y * g->ply.move_speed;
	check = (t_int){(int)buffer.x, (int)buffer.y};
	if (get_map_pos(check, &g->map) == '0')
	{
		*ply = (t_point){buffer.x, buffer.y};
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

int	update_ply_move(t_ply *p, const t_game *g)
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
