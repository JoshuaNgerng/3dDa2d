/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast__.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:07 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/05 17:37:21 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_wall(const t_game *g, double x, double y)
{
	if (x < 0 || x >= g->map.height)
		return (0);
	if (y < 0 || y >= g->map.width)
		return (0);
	if (g->map.map[(int)x * g->map.width + (int)y] == '1')
		return (1);
	return (0);
}

static double	raycasting_vert(t_game *g, const t_ray *r, t_ray_dist *rd)
{
	int	dir;
	int	iter;

	if (r->angle == 0 || r->angle == M_PI)
		return (-1);
	dir = 1;
	if (r->angle > M_PI)
		dir = -1;
	rd->x_offset = 1.0 - modf(r->start_y, &rd->y_offset) * dir;
	rd->y_offset = rd->x_offset * r->tan;//r->start_y - (r->start_x - rd->x_offset) * r->tan;
	rd->ray_x = r->start_x + rd->x_offset;
	rd->ray_y = r->start_y + rd->y_offset;
	// printf("vert start [%lf][%lf], end [%lf][%lf]\n", r->start_x, r->start_y, rd->ray_x, rd->ray_y);
	if (check_wall(g, rd->ray_x, rd->ray_y))
		return (get_distance(r->start_x, r->start_y, rd->ray_x, rd->ray_y));
	rd->y_offset = 0.05 * dir;
	rd->x_offset = rd->y_offset * r->tan;
	iter = 0;
	while (++ iter < r->dof)
	{
		rd->ray_x += rd->x_offset;
		rd->ray_y += rd->y_offset;
		if (check_wall(g, rd->ray_x, rd->ray_y))
			return (get_distance(r->start_x, r->start_y, rd->ray_x, rd->ray_y));
	}
	return (-1);
}

static double	raycast_horizon(t_game *g, const t_ray *r, t_ray_dist *rd)
{
	int	iter;
	int	dir;

	if (r->angle == 0 || r->angle == M_PI)
		return (-1);
	dir = 1;
	if (r->angle > M_PI)
		dir = -1;
	rd->y_offset = 1.0 - modf(r->start_x, &rd->x_offset) * dir;
	rd->x_offset = rd->y_offset / r->tan * dir;//r->start_x - (r->start_y - rd->y_offset) / r->tan;
	rd->ray_x = r->start_x + rd->x_offset;
	rd->ray_y = r->start_y + rd->y_offset;
	// printf("hori start [%lf][%lf], end [%lf][%lf]\n", r->start_x, r->start_y, rd->ray_x, rd->ray_y);
	if (check_wall(g, rd->ray_x, rd->ray_y))
		return (get_distance(r->start_x, r->start_y, rd->ray_x, rd->ray_y));
	rd->x_offset = 0.05 * dir;
	rd->y_offset = rd->x_offset / r->tan;
	iter = 0;
	while (++ iter < r->dof)
	{
		rd->ray_x += rd->x_offset;
		rd->ray_y += rd->y_offset;
		if (check_wall(g, rd->ray_x, rd->ray_y))
			return (get_distance(r->start_x, r->start_y, rd->ray_x, rd->ray_y));
	}
	return (-1);
}

void	raycasting_walls(t_game *g)
{
	t_ray		r;
	t_ray_dist	horizon;
	t_ray_dist	verti;
	t_ray_dist	*ptr;

	r.no_ray = -1;
	r.dof = g->setting.depth_of_focus;
	r.start_x = g->ply.pos.x;
	r.start_y = g->ply.pos.y;
	horizon.type = 'h';
	horizon.type = 'v';
	new_angle(&r.angle, g->ply.view - g->setting.angle_start);
	while (++ r.no_ray < RAY_FREQ)
	{
		r.tan = tan(r.angle);
		horizon.dist = raycast_horizon(g, &r, &horizon);
		verti.dist = raycasting_vert(g, &r, &verti);
		ptr = &verti;
		if ((horizon.dist >= 0 && horizon.dist < verti.dist) || verti.dist < 0)
			ptr = &horizon;
		ptr->dist *= cos(new_angle(NULL, g->ply.view - r.angle));
		draw_wall(g, ptr, r.no_ray, r.angle);
		new_angle(&r.angle, r.angle + g->setting.angle_delta);
	}
}
