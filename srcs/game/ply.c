/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:21:04 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 15:57:32 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
set player info
col is the y pos of the ply, x pos is set outside of the func from the row 
dir is the ply orientation from map
if x pos is more than zero means that ply already been set prev
dup ply error
*/
int	set_ply_pos(int col, char dir, t_ply *p)
{
	if (p->pos.x >= 0)
		return (1);
	p->pos.y = (double)col;
	if (dir == 'N')
	{
		p->n_dir = (t_point){.x = -1., .y = 0.};
		p->view = (t_point){.x = 0., .y = p->fov};
	}
	else if (dir == 'E')
	{
		p->n_dir = (t_point){.x = 0., .y = 1.};
		p->view = (t_point){.x = p->fov, .y = 0.};
	}
	else if (dir == 'S')
	{
		p->n_dir = (t_point){.x = 1., .y = 0.};
		p->view = (t_point){.x = 0., .y = -p->fov};
	}
	else if (dir == 'W')
	{
		p->n_dir = (t_point){.x = 0., .y = -1.};
		p->view = (t_point){.x = -p->fov, .y = 0.};
	}
	p->p_dir = (t_point){.x = -p->n_dir.y, .y = p->n_dir.x};
	return (0);
}

/*
(rotation matrix) X (ply dir matrix) = (new ply dir matrix)
2x2 matrix mutiply 2x1 matrix formula
rotate matrix formula
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
used to rotate player
*/
static void	rotation_matrix(t_point *dst, double sin_, double cos_)
{
	t_point	buffer;

	buffer = (t_point){.x = dst->x, .y = dst->y};
	dst->x = (buffer.x * cos_) - (buffer.y * sin_);
	dst->y = (buffer.x * sin_) + (buffer.y * cos_);
}

/*
update player current pos
ply doesnt move if there is no valid spot

ply ply pos
move ply movement dir
g - game struct ref to important info like map
dir - 1 or -1 depending on left/right or forward/backward

map_pos -> check dist is double the actual ply move to avoid vis bug (like clipping into walls)

'0' or 'D' (door in open state)
otherwise ply doesnt move
*/
static
int	update_move(t_point *ply, const t_point *move, const t_game *g, int dir)
{
	double	step_size;
	t_int	update;
	t_int	map_pos;

	update.y = 0;
	step_size = dir * move->x * g->ply.move_speed;
	map_pos = (t_int){(int)(ply->x + 2 * step_size), (int)(ply->y)};
	update.x = get_map_pos(map_pos, &g->map);
	if (update.x == '0'
		|| (update.x == 'D' && get_door_status(&g->door, map_pos, NULL) == 1))
	{
		ply->x += step_size;
		update.y = 1;
	}
	step_size = dir * move->y * g->ply.move_speed;
	map_pos = (t_int){(int)(ply->x), (int)(ply->y + 2 * step_size)};
	update.x = get_map_pos(map_pos, &g->map);
	if (update.x == '0'
		|| (update.x == 'D' && get_door_status(&g->door, map_pos, NULL) == 1))
	{
		ply->y += step_size;
		update.y = 1;
	}
	return (update.y);
}

/*
matrix mutliplication to update the player orietation
*/
static int	update_angle(t_ply *p, int dir)
{
	rotation_matrix(&p->n_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->p_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->view, p->rotate_sin[dir], p->rotate_cos[dir]);
	return (1);
}

/*
if ply move options (bits) is set to 1
update the corresponding options
return 0 if ply doesnt move pos num otherwise
*/
int	update_ply_move(t_ply *p, const t_game *g)
{
	int	update;

	update = 0;
	if (p->move_options & rotate_left)
		update += update_angle(p, 0);
	else if (p->move_options & rotate_right)
		update += update_angle(p, 1);
	if (p->move_options & move_left)
		update += update_move(&p->pos, &p->p_dir, g, 1);
	else if (p->move_options & move_right)
		update += update_move(&p->pos, &p->p_dir, g, -1);
	if (p->move_options & forward)
		update += update_move(&p->pos, &p->n_dir, g, 1);
	else if (p->move_options & backward)
		update += update_move(&p->pos, &p->n_dir, g, -1);
	return (update);
}
