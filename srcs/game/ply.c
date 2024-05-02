/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:21:04 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/02 17:43:47 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	update_move(t_point *ply, const t_point *move, const t_game *g, int dir)
{
	int		update;
	t_point	check;

	update = 0;
	check = (t_point){ply->x, ply->y};
	check.x += dir * move->x * g->ply.move_speed;
	// printf("testing dir,%d move,%lf move_speed,%lf\n", dir, move->x, g->ply.move_speed);
	// printf("check 1 (%lf)(%lf)\n", check.x, check.y);
	if (get_map_pos(&check, &g->map) == '0')
	{
		*ply = (t_point){check.x, check.y};
		// printf("new pos 1 (%lf)(%lf)\n", ply->x, ply->y);
		update = 1;
	}
	check = (t_point){ply->x, ply->y};
	check.y += dir * move->y * g->ply.move_speed;
	// printf("testing dir,%d move,%lf move_speed,%lf\n", dir, move->y, g->ply.move_speed);
	// printf("check 2 (%lf)(%lf)\n", check.x, check.y);
	if (get_map_pos(&check, &g->map) == '0')
	{
		*ply = (t_point){check.x, check.y};
		// printf("new pos 2 (%lf)(%lf)\n", ply->x, ply->y);
		update = 1;
	}
	return (update);
}

int	update_angle(t_ply *p, int dir)
{
	// if (!dir)
	// 	printf("detect look left\n");
	// else
	// 	printf("detect look right\n");
	rotation_matrix(&p->n_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->p_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->view, p->rotate_sin[dir], p->rotate_cos[dir]);
	return (1);
}

int	test_printf(char *s, int i)
{
	(void)s;
	// printf("%s\n", s);
	return (i);
}

int	update_ply_move(t_ply *p, const t_game *g)
{
	int	update;

	update = 0;
	if (p->move_options & rotate_left)
		update = update_angle(p, 0);
	else if (p->move_options & rotate_right)
		update =  update_angle(p, 1);
	if (p->move_options & move_left)
		update = update_move(&p->pos, &p->p_dir, g, test_printf("detect left", 1));
	else if (p->move_options & move_right)
		update = update_move(&p->pos, &p->p_dir, g, test_printf("detect left", -1));
	if (p->move_options & forward)
		update = update_move(&p->pos, &p->n_dir, g, test_printf("detect up", 1));
	else if (p->move_options & backward)
		update = update_move(&p->pos, &p->n_dir, g, test_printf("detect down", -1));
	return (update);
}
