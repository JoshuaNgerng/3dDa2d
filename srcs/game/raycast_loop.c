/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:34:52 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/24 18:52:31 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static
t_ray_comp	raycast_comp_init(double ply_pos, double ray_perp, double ray_ref)
{
	t_ray_comp	buffer;

	buffer = (t_ray_comp){.map_check = (int)ply_pos,
		.check_dist = modf(ply_pos, &(double){0}), .step_dir = -1,
		.step_size = sqrt(1 + pow(ray_perp / ray_ref, 2.))};
	if (ray_ref >= 0.)
	{
		buffer.step_dir = 1;
		buffer.check_dist = 1.0 - modf(ply_pos, &(double){0});
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

static int	raycast_loop(t_ray *r, const t_game *g)
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

void	raycasting_walls(t_img *img, const t_game *g)
{
	t_ray	ray;

	ray.ray_no = -1;
	while (++ ray.ray_no < g->setting.win_width)
	{
		if (raycast_loop(&ray, g))
		{
			draw_door(img, &ray, g);
			draw_key(img, &ray, g);
			continue ;
		}
		draw_wall(img, &ray, g);
		draw_door(img, &ray, g);
		draw_key(img, &ray, g);
	}
}
