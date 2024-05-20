/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/20 14:36:54 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	mouse_set_ply(int key, int pos_x, int pos_y, t_game *g)
{
	int		half_width;
	(void) pos_y;

	if (key != 1)
		return (0);
	half_width = g->setting.win_width / 2;
	if (pos_x == half_width)
		return (0);
	if (pos_x < half_width)
		g->ply.move_options |= rotate_left;
	else
		g->ply.move_options |= rotate_right;
	return (0);
}

int	mouse_unset_ply(int key, int pos_x, int pos_y, t_game *g)
{
	(void) pos_x;
	(void) pos_y;

	if (key != 1)
		return (0);
	g->ply.move_options &= ~(rotate_left + rotate_right);
	return (0);
}

int	set_ply_mov(int key, t_game *g)
{
	if (key == esc)
		free_exit(g, 0);
	if (key == up || key == wkey)
		g->ply.move_options |= forward;
	else if (key == down || key == skey)
		g->ply.move_options |= backward;
	else if (key == akey)
		g->ply.move_options |= move_left;
	else if (key == dkey)
		g->ply.move_options |= move_right;
	else if (key == left || key == qkey)
		g->ply.move_options |= rotate_left;
	else if (key == right || key == ekey)
		g->ply.move_options |= rotate_right;
	else if (key == lshift || key == rshift)
		g->ply.move_options |= interact_door;
	else if (key == mkey)
		g->ply.move_options ^= map_option;
	return (0);
}

int	unset_ply_mov(int key, t_game *g)
{
	if (key == up || key == wkey)
		g->ply.move_options &= ~forward;
	if (key == down || key == skey)
		g->ply.move_options &= ~backward;
	if (key == akey)
		g->ply.move_options &= ~move_left;
	if (key == dkey)
		g->ply.move_options &= ~move_right;
	if (key == left || key == qkey)
		g->ply.move_options &= ~rotate_left;
	if (key == right || key == ekey)
		g->ply.move_options &= ~rotate_right;
	return (0);
}

int	main_loop(t_game *g)
{
	if (update_ply_move(&g->ply, g))
		raycasting_walls(&g->scene, g);
	if (g->ply.move_options & interact_door)
		update_door(&g->map, &g->ply, &g->door);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->scene.img, 0, 0);
	if (g->ply.move_options & map_option)
		create_minimap(&g->minimap, &g->mlx, g);
	g->ply.move_options &= ~interact_door;
	update_door_counter(&g->door);
	update_key(&g->key, &g->ply);
	return (0);
}
