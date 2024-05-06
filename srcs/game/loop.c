/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/06 08:49:39 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	set_ply_mov(int key, t_game *g)
{
	if (key == esc)
		free_exit(g, 0);
	if (key == up || key == wkey)
		g->ply.move_options |= forward;
	if (key == down || key == skey)
		g->ply.move_options |= backward;
	if (key == akey)
		g->ply.move_options |= move_left;
	if (key == dkey)
		g->ply.move_options |= move_right;
	if (key == left || key == qkey)
		g->ply.move_options |= rotate_left;
	if (key == right || key == ekey)
		g->ply.move_options |= rotate_right;
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

int	animation(t_game *g)
{
	// static int i;
	if (!update_ply_move(&g->ply, g))
		return (0);
	// printf("change detected %d", i ++);
	// printf(", ply pos (%lf)(%lf)", g->ply.pos.x, g->ply.pos.y);
	// printf(", ply rot (%lf)(%lf)\n", g->ply.view.x, g->ply.view.y);
	generate_scene(g);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->scene.img, 0, 0);
	return (0);
}
