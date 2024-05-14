/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:34:52 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 17:29:11 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycast_set_dist(t_ray_comp *r, double dir, double ply_pos, int map_pos)
{
	if (dir < 0.)
	{
		r->step_dir = -1;
		r->check_dist = ply_pos - (double)map_pos;
	}
	else
	{
		r->step_dir = 1;
		r->check_dist = (double)(map_pos + 1) - ply_pos;
	}
}

void	raycast_init(t_ray *r, int ray_no, const t_game *g)
{
	double	x_pos;

	x_pos = ((2. * (double)ray_no) / (double)g->setting.win_width) - 1.;
	r->ray_dir.x = g->ply.n_dir.x + g->ply.view.x * x_pos;
	r->ray_dir.y = g->ply.n_dir.y + g->ply.view.y * x_pos;
	r->hori.map_check = (int)g->ply.pos.x;
	r->verti.map_check = (int)g->ply.pos.y;
	r->hori.step_size = sqrt(1 + pow(r->ray_dir.y / r->ray_dir.x, 2.));
	r->verti.step_size = sqrt(1 + pow(r->ray_dir.x / r->ray_dir.y, 2.));
	raycast_set_dist(&r->hori, r->ray_dir.x, g->ply.pos.x, r->hori.map_check);
	raycast_set_dist(&r->verti, r->ray_dir.y, g->ply.pos.y, r->verti.map_check);
	r->hori.check_dist *= r->hori.step_size;
	r->verti.check_dist *= r->verti.step_size;
}

void	iter_raycast_loop(t_ray_comp *r, int *side_ptr, int side)
{
	r->map_check += r->step_dir;
	r->check_dist += r->step_size;
	*side_ptr = side;
}

void	raycast_fin(t_ray *r, const t_ply *p)
{
	double	hit_dist;

	if (r->side == horizontal)
	{
		hit_dist = (double)(r->hori.map_check + ((1 - r->hori.step_dir) / 2));
		r->perp_dist = fabs((hit_dist - p->pos.x) / r->ray_dir.x);
		r->hitpoint = p->pos.y + r->perp_dist * r->ray_dir.y;
		if (r->ray_dir.x < 0)
			r->side = west;
		else
			r->side = east;
		return ;
	}
	hit_dist = (double)(r->verti.map_check + ((1 - r->verti.step_dir) / 2));
	r->perp_dist = fabs((hit_dist - p->pos.y) / r->ray_dir.y);
	r->hitpoint = p->pos.x + r->perp_dist * r->ray_dir.x;
	if (r->ray_dir.y < 0)
		r->side = north;
	else
		r->side = south;
}

int	raycast_loop(t_ray *r, int ray_no, const t_game *g)
{
	int	map_check;

	raycast_init(r, ray_no, g);
	while (r->hori.check_dist < g->ply.depth_of_focus
		|| r->verti.check_dist < g->ply.depth_of_focus)
	{
		if (r->hori.check_dist < r->verti.check_dist)
			iter_raycast_loop(&r->hori, &r->side, horizontal);
		else
			iter_raycast_loop(&r->verti, &r->side, vertical);
		map_check = get_map_pos((t_int){(int)r->hori.map_check,
				(int)r->verti.map_check}, &g->map);
		if (map_check < 0)
			return (1);
		if (map_check != '0')
		{
			if (map_check == 'D')
				r->door = get_counter(&r->index, &g->door);
			break ;
		}
	}
	raycast_fin(r, &g->ply);
	r->hitpoint -= floor(r->hitpoint);
	return (0);
}
