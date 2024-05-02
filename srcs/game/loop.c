/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/02 17:35:10 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
static void	change_player_view(double new_view, t_ply *p)
{
	p->view = new_view;
	if (p->view < 0)
		p->view += M_PI;
	else if (p->view > M_PI)
		p->view -= M_PI;
	p->delta.y = sin(p->view) * MOVE_SPEED;
	p->delta.x = cos(p->view) * MOVE_SPEED;
}

static void	change_player_pos(t_game *g, t_point *ply_pos, 
	double new_x, double new_y)
{
	int	check_x;
	int	check_y;

	check_x = (int)(ply_pos->x + new_x + new_x);
	check_y = (int)(ply_pos->y + new_y + new_y);
	// printf("check new pos %d %d\n", check_x, check_y);
	// printf("test %c %c %c\n", g->map[check_x][(int)ply_pos->y], g->map[(int)ply_pos->x][check_y], g->map[check_x][check_y]);
	if (check_x < 0 && check_x >= g->map.heigth && check_y >= g->map.width)
		return ;
	if (g->map.map[check_x * g->map.width + check_y] == '0')
	{
		ply_pos->x += new_x;
		ply_pos->y += new_y;
		return ;
	}
	if (check_x >= 0 && check_x < g->map.heigth && g->map.map[check_x * g->map.width + (int)ply_pos->y] == '0')
		ply_pos->x += new_x;
	if (check_y >= 0 && check_y < g->map.width && g->map.map[(int)ply_pos->x * g->map.width + check_y] == '0')
		ply_pos->y += new_y;
}

// pretend no mouse inputs
int	handle_input(int key, t_game *g)
{
	if (key == esc)
		free_exit(g, 0);
	else if (key == up || key == wkey)
		change_player_pos(g, &g->ply.pos, - g->ply.delta.x, - g->ply.delta.y);
	else if (key == down || key == skey)
		change_player_pos(g, &g->ply.pos, g->ply.delta.x, g->ply.delta.y);
	else if (key == left || key == akey)
		change_player_view(g->ply.view - ROTATION_SPEED, &g->ply);
	else if (key == right || key == dkey)
		change_player_view(g->ply.view + ROTATION_SPEED, &g->ply);
	// printf("ply pos %lf, %lf %lf\n", g->ply.pos.x, g->ply.pos.y, g->ply.view);
	return (0);
}
*/

int	set_ply_mov(int key, t_game *g)
{
	if (key == esc)
		free_exit(g, 0);
	if (key == up || key == wkey)
	{
		printf("test up\n");
		g->ply.move_options |= forward;
	}
	if (key == down || key == skey)
	{
		printf("test down\n");
		g->ply.move_options |= backward;
	}
	if (key == akey)
	{
		printf("test left\n");
		g->ply.move_options |= move_left;
	}
	if (key == dkey)
	{
		printf("test right\n");
		g->ply.move_options |= move_right;
	}
	if (key == left || key == qkey)
	{
		printf("test look left\n");
		g->ply.move_options |= rotate_left;
	}
	if (key == right || key == ekey)
	{
		printf("test look right\n");
		g->ply.move_options |= rotate_right;
	}
	return (0);
}

int	unset_ply_mov(int key, t_game *g)
{
	// printf("detect key release\n");
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
