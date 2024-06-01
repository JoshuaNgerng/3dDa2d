/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:28:57 by jngerng           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/25 16:18:32 by lchew            ###   ########.fr       */
=======
/*   Updated: 2024/05/29 13:53:16 by jngerng          ###   ########.fr       */
>>>>>>> bonus
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static
void	raycast_fin(t_ray_fin *fin, int type, const t_ray *r, const t_ply *p)
{
	double	hit_dist;

	fin->type = type;
	if (r->side == horizontal)
	{
		hit_dist = (double)(r->hori.map_check - p->pos.x + ((1 - r->hori.step_dir) / 2));
		fin->perp_dist = fabs(hit_dist / r->ray_dir.x);
		fin->hitpoint = p->pos.y + fin->perp_dist * r->ray_dir.y;
		if (r->ray_dir.x < 0)
			fin->side = south;
		else
			fin->side = north;
		return ;
	}
	hit_dist = (double)(r->verti.map_check - p->pos.y + ((1 - r->verti.step_dir) / 2));
	fin->perp_dist = fabs(hit_dist / r->ray_dir.y);
	fin->hitpoint = p->pos.x + fin->perp_dist * r->ray_dir.x;
	if (r->ray_dir.y < 0)
		fin->side = west;
	else
		fin->side = east;
}

int	raycast_check(t_ray *r, const t_game *g)
{
	static int	shadow = 0;
	int			map_char;
	t_int		map_pos;

	map_pos = (t_int){r->hori.map_check, r->verti.map_check};
	map_char = get_map_pos(map_pos, &g->map);
	if (map_char < 0)
		return (-1);
	if (map_char == '0')
	{
		if (!shadow)
			return (0);
		shadow = 0;
		if (r->obj_iter == MAX_RENDER_OBJ)
			return (0);
		r->fin[r->obj_iter].index = r->fin[r->obj_iter - 1].index;
		return (raycast_fin(&r->fin[r->obj_iter ++], door_, r, &g->ply), 0);
	}
	shadow = 0;
	if (map_char == '1')
		return (raycast_fin(&r->fin[r->obj_iter ++], wall, r, &g->ply), 1);
	if (r->obj_iter == MAX_RENDER_OBJ)
		return (0);
	if (map_char == 'D')
	{
		if (get_door_status(&g->door, map_pos, &r->fin[r->obj_iter].index) == -1)
			return (raycast_fin(&r->fin[r->obj_iter ++], door, r, &g->ply), 1);
		raycast_fin(&r->fin[r->obj_iter ++], door, r, &g->ply);
		shadow = 1;
	}
	return (0);
}
