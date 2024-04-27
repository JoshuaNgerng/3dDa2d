/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:20:32 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/01 16:32:55 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_walls(t_ray *r, t_game *g, t_ray_fin *ptr)
{
	int	x;
	int	y;

	x = (int)r->ray_x;
	y = (int)r->ray_y;
	// printf("test coord %d %d lim %d %d\n", x, y, g->row, g->size);
	if (x >= 0 && x < g->row && y >= 0 && y < g->size)
	{
		// printf("check map %c\n", g->map[x][y]);
		if (g->map[x][y] == '1')
		{
			ptr->ray_x = r->ray_x;
			ptr->ray_y = r->ray_y;
			ptr->dist = get_distance(g->ply.pos.x, g->ply.pos.y,
					ptr->ray_x, ptr->ray_y);
			return (1);
		}
	}
	r->ray_x += r->x_offset;
	r->ray_y += r->y_offset;
	return (0);
}

static void	ray_horizontal_init(t_ray *r, t_game *g, t_ray_fin *horizon)
{
	r->y_offset = 0;
	if (r->angle > M_PI)
	{
		r->ray_y = g->ply.pos.y;
		r->y_offset = -1;
	}
	else if (r->angle < M_PI)
	{
		r->ray_y = g->ply.pos.y + 1;
		r->y_offset = 1;
	}
	r->ray_x = (g->ply.pos.y - r->ray_y) * r->atan + g->ply.pos.x;
	// printf("hor p1 %lf p2 %lf\n", (g->ply.pos.y - r->ray_y) * r->atan, g->ply.pos.x);
	r->x_offset = -r->y_offset * r->atan;
	r->dof = -1;
	if (!r->angle || r->angle == M_PI)
	{
		r->ray_x = g->ply.pos.x;
		r->ray_y = g->ply.pos.y;
		r->dof = DEPTH_OF_FOCUS;
	}
	// printf("ori: %lf %lf\n", r->ray_x, r->ray_y);
	while (++ r->dof < DEPTH_OF_FOCUS)
	{
		if (check_walls(r, g, horizon))
			break ;
	}
	// printf("end: %lf %lf\n", r->ray_x, r->ray_y);
}

static void	ray_vertical_init(t_ray *r, t_game *g, t_ray_fin *vert)
{
	r->x_offset = 0;
	if (r->angle > M_PI_2 && r->angle < M_PI_4 * 3)
	{
		r->ray_x = g->ply.pos.x;
		r->x_offset = -1;
	}
	else if (r->angle < M_PI_2 || r->angle > M_PI_4 * 3)
	{
		r->ray_x = g->ply.pos.x + 1;
		r->x_offset = 1;
	}
	r->ray_y = (g->ply.pos.x - r->ray_x) * r->ntan + g->ply.pos.y;
	// printf("ver p1 %lf p2 %lf\n", (g->ply.pos.x - r->ray_x) * r->ntan, g->ply.pos.y);
	r->y_offset = -r->x_offset * r->ntan;
	r->dof = -1;
	if (!r->angle || r->angle == M_PI)
	{
		r->ray_x = g->ply.pos.x;
		r->ray_y = g->ply.pos.y;
		r->dof = DEPTH_OF_FOCUS;
	}
	while (++ r->dof < DEPTH_OF_FOCUS)
	{
		if (check_walls(r, g, vert))
			break ;
	}
}

static void	raycast_init(t_ray *r, t_ray_fin *h, t_ray_fin *v, const t_point *p)
{
	double	tangent;

	tangent = tan(r->angle);
	v->dist = (double)INT32_MAX;
	h->dist = v->dist;
	v->ray_x = p->x;
	v->ray_y = p->y;
	h->ray_x = p->x;
	h->ray_y = p->y;
	r->atan = -1 / tangent;
	r->ntan = -tangent;
}

void	raycasting_walls(t_game *g)
{
	// static int	i;
	t_ray		ray;
	t_ray_fin	vertical;
	t_ray_fin	horizontal;
	t_ray_fin	fin;

	ray.no_ray = -1;
	new_angle(&ray.angle, g->ply.view - DEGREE * RAY_FREQ / 2);
	while (++ ray.no_ray < RAY_FREQ)
	{
		ray.y_offset = 0;
		raycast_init(&ray, &horizontal, &vertical, &g->ply.pos);
		ray_horizontal_init(&ray, g, &horizontal);
		ray_vertical_init(&ray, g, &vertical);
		draw_wall(&fin, &ray, calculate_wall(&fin, 
			&horizontal, &vertical, ray.angle), g);
		// printf("ray no:%d, ")
		new_angle(&ray.angle, ray.angle + DEGREE);
	}
}
