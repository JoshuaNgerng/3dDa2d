/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:28:57 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/25 03:06:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static
void	raycast_fin(t_ray_fin *fin, int type, const t_ray *r, const t_ply *p)
{
	double	hit_dist;

	if (r->side == horizontal)
	{
		hit_dist = (double)(r->hori.map_check + ((1 - r->hori.step_dir) / 2));
		fin->perp_dist = fabs((hit_dist - p->pos.x) / r->ray_dir.x);
		fin->hitpoint = p->pos.y + fin->perp_dist * r->ray_dir.y;
		if (r->ray_dir.x < 0)
			fin->side = south;
		else
			fin->side = north;
		fin->type = type;
		return ;
	}
	hit_dist = (double)(r->verti.map_check + ((1 - r->verti.step_dir) / 2));
	fin->perp_dist = fabs((hit_dist - p->pos.y) / r->ray_dir.y);
	fin->hitpoint = p->pos.x + fin->perp_dist * r->ray_dir.x;
	if (r->ray_dir.y < 0)
		fin->side = west;
	else
		fin->side = east;
	fin->type = type;
}

int	raycast_check(t_ray *r, const t_game *g)
{
	static int	index;
	int		map_char;
	t_int	map_pos;

	map_pos = (t_int){r->hori.map_check, r->verti.map_check};
	map_char = get_map_pos(map_pos, &g->map);
	if (map_char < 0)
		return (-1);
	if (map_char == '0')
		return (0);
	if (map_char == '1')
		return (raycast_fin(&r->fin[wall], wall, r, &g->ply), 1);
	else if (map_char == 'D')
	{
		if (get_door_status(&g->door, map_pos, &r->fin[wall].index) == -1)
		{
			// printf("wall as door %d\n", index ++);
			return (raycast_fin(&r->fin[wall], door, r, &g->ply), 1);
		}
		else if (r->fin[door].type == undef)
		{
			// printf("door init %d\n", index ++);
			raycast_fin(&r->fin[door], door, r, &g->ply);
			r->fin[door].index = r->fin[wall].index;
		}
		// printf("door not capture %d\n", index ++);
	}
	else if (map_char == 'K')
	{
		raycast_fin(&r->fin[key], key, r, &g->ply);
		r->fin[key].index = get_asset_index(&g->key, map_pos);
	}
	return (0);
}
