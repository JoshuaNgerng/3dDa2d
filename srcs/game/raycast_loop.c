/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:34:52 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/16 16:51:09 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	raycast_fin(t_ray *r, int type, const t_ply *p)
{
	double	hit_dist;

	if (r->side == horizontal)
	{
		hit_dist = (double)(r->hori.map_check + ((1 - r->hori.step_dir) / 2));
		r->fin[type].perp_dist = fabs((hit_dist - p->pos.x) / r->ray_dir.x);
		r->fin[type].hitpoint = p->pos.y + r->fin[type].perp_dist * r->ray_dir.y;
		if (r->ray_dir.x < 0)
			r->fin[type].side = west;
		else
			r->fin[type].side = east;
		return (1);
	}
	hit_dist = (double)(r->verti.map_check + ((1 - r->verti.step_dir) / 2));
	r->fin[type].perp_dist = fabs((hit_dist - p->pos.y) / r->ray_dir.y);
	r->fin[type].hitpoint = p->pos.x + r->fin[type].perp_dist * r->ray_dir.x;
	if (r->ray_dir.y < 0)
		r->fin[type].side = north;
	else
		r->fin[type].side = south;
	r->fin[type].type = type;
	return (1);
}

int	raycast_check(t_ray *r, const t_game *g)
{
	int		map_char;
	t_int	map_pos;

	map_pos = (t_int){r->hori.map_check, r->verti.map_check};
	map_char = get_map_pos(map_pos, &g->map);
	if (map_char < 0)
		return (-1);
	if (map_char == 'D')
	{
		if (get_door_status(&g->door, map_pos) == -1)
		{
			raycast_fin(r, wall, &g->ply);
			r->fin[wall].type = door;
			return (raycast_fin(r, wall, &g->ply));
		}
		raycast_fin(r, door, &g->ply);
	}
	if (map_char == '1')
		return (raycast_fin(r, wall, &g->ply));
	else if (map_char == 'K')
		raycast_fin(r, key, &g->ply);;
	return (0);
}

static t_ray_comp	raycast_comp_init(double ply_pos, double ray_perp, double ray_ref)
{
	int			ply_pos_roundoff;
	t_ray_comp	buffer;

	ply_pos_roundoff = (int)(ply_pos);
	buffer = (t_ray_comp){.map_check = ply_pos_roundoff,
		.check_dist = ply_pos - (double)(ply_pos_roundoff), .step_dir = -1,
		.step_size = sqrt(1 + pow(ray_perp / ray_ref, 2.))};
	if (ray_ref >= 0.)
	{
		buffer.step_dir = 1;
		buffer.check_dist = (double)ply_pos_roundoff + 1.0 - ply_pos;
	}
	buffer.check_dist *= buffer.step_size;
	return (buffer);
}

static void	raycast_init(t_ray *r, const t_game *g)
{
	double	x_pos;

	x_pos = ((2. * (double)(r->ray_no) / (double)g->setting.win_width) - 1.);
	r->ray_dir.x = g->ply.n_dir.x + g->ply.view.x * x_pos;
	r->ray_dir.y = g->ply.n_dir.y + g->ply.view.y * x_pos;
	r->hori = raycast_comp_init(g->ply.pos.x, r->ray_dir.y, r->ray_dir.x);
	r->verti = raycast_comp_init(g->ply.pos.y, r->ray_dir.x, r->ray_dir.y);
	r->fin[0] = (t_ray_fin){.type = undef};
	r->fin[1] = (t_ray_fin){.type = undef};
	r->fin[2] = (t_ray_fin){.type = undef};
}

int	raycast_loop(t_ray *r, const t_game *g)
{
	int	check;

	raycast_init(r, g);
	while (r->hori.check_dist < g->ply.depth_of_focus
		|| r->verti.check_dist < g->ply.depth_of_focus)
	{
		if (r->hori.check_dist < r->verti.check_dist)
		{
			r->hori.map_check += r->hori.step_dir;
			r->hori.check_dist += r->hori.step_size;
			r->side = horizontal;
		}
		else
		{
			r->verti.map_check += r->verti.step_dir;
			r->verti.check_dist += r->verti.step_size;
			r->side = vertical;
		}
		check = raycast_check(r, g);
		if (check < 0)
			return (1);
		if (check > 0)
			return (0);
	}
	return (1);
}
