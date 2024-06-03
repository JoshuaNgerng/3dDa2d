/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:28:57 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/01 20:04:32 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Finalizes raycasting by calculating hit and perpendicular distances.
 *
 * This function determines the hit distance based on the ray's side (horizontal
 * or not). It then calculates the perpendicular distance and hit point. The 
 * side of the hit is determined based on the direction of the ray.
 *
 * @param fin The final raycast result.
 * @param type The type of the raycast.
 * @param r The ray being cast.
 * @param p The player.
 */
static
void	raycast_fin(t_ray_fin *fin, int type, const t_ray *r, const t_ply *p)
{
	double	hit_dist;

	fin->type = type;
	if (r->side == horizontal)
	{
		hit_dist = (double)(r->hori.map_check - p->pos.x \
			+ ((1 - r->hori.step_dir) / 2));
		fin->perp_dist = fabs(hit_dist / r->ray_dir.x);
		fin->hitpoint = p->pos.y + fin->perp_dist * r->ray_dir.y;
		if (r->ray_dir.x < 0)
			fin->side = south;
		else
			fin->side = north;
		return ;
	}
	hit_dist = (double)(r->verti.map_check - p->pos.y \
		+ ((1 - r->verti.step_dir) / 2));
	fin->perp_dist = fabs(hit_dist / r->ray_dir.y);
	fin->hitpoint = p->pos.x + fin->perp_dist * r->ray_dir.x;
	if (r->ray_dir.y < 0)
		fin->side = west;
	else
		fin->side = east;
}

/**
 * @brief Performs a raycast check on the game map.
 *
 * This function performs a raycast check on the game map. It determines the 
 * character at the map position being checked and handles it accordingly. If 
 * the character is '0', it handles shadows and doors. If the character is '1', 
 * it handles walls. If the character is 'D', it handles doors.
 *
 * @param r The ray being cast.
 * @param g The game state.
 * @return Returns 0 for shadows and doors, 1 for walls, and -1 for 
 * out of bounds.
 */
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
	if (map_char == 'D')
	{
		if (get_door_stat(&g->door, map_pos, &r->fin[r->obj_iter].index) == -1)
			return (raycast_fin(&r->fin[r->obj_iter ++], door, r, &g->ply), 1);
		if (r->obj_iter == MAX_RENDER_OBJ)
			return (0);
		raycast_fin(&r->fin[r->obj_iter ++], door, r, &g->ply);
		shadow = 1;
	}
	return (0);
}
