/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:34:52 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/29 17:14:00 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycast_set_dist(t_ray_comp *r, double dir, double ply_pos, int map_pos)
{
	if (dir < 0)
	{
		r->step_dir = -1;
		r->check_dist = (double)map_pos - ply_pos;
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

	x_pos = 2 * ray_no / g->setting.win_width - 1;
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
	r->step_dir += r->step_size;
	*side_ptr = side;
}

double	raycast_fin(t_ray *r, const t_ply *p)
{
	double	perp_dist;

	if (r->side == horizontal)
	{
		perp_dist = r->hori.check_dist - p->pos.x + ((1 - r->hori.step_dir) / 2);
		if (r->ray_dir.x < 0)
			r->side = west;
		else
			r->side = east;
		return (fabs(perp_dist / r->ray_dir.x));
	}
	perp_dist = r->verti.check_dist - p->pos.y + ((1 - r->verti.step_dir) / 2);
	if (r->ray_dir.y < 0)
		r->side = north;
	else
		r->side = south;
	return (fabs(perp_dist / r->ray_dir.y));
}

int	raycast_loop(t_ray *r, int ray_no, const t_game *g)
{
	int		no_check; // try max dist check , instead max iter check
	int		map_checker;
	t_point	map_pos;

	raycast_init(r, ray_no, g);
	no_check = -1;
	while (++ no_check < g->setting.depth_of_focus)
	{
		if (r->ray_dir.x < r->ray_dir.y)
			iter_raycast_loop(&r->hori, &r->side, horizontal);
		else
			iter_raycast_loop(&r->verti, &r->side, vertical);
		map_pos = (t_point){.x = (double)r->hori.map_check, .y = (double)r->verti.map_check};
		map_checker = get_map_pos(&map_pos, &g->map);
		if (map_checker < 0)
			return (1);
		if (map_checker == '1')
			break ;
	}
	r->height = fabs(g->setting.win_height / raycast_fin(r, &g->ply));
	return (0);
}
