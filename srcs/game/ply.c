/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:21:04 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 15:57:32 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Set the player position and orientation.
 *
 * This function sets the player's position and orientation based on the given
 * column, direction, and player struct. The x position is set outside of the
 * function from the row. If the x position is already greater than or equal to
 * zero, it means that the player has already been set previously, and an error
 * is returned.
 *
 * @param col The column position of the player.
 * @param dir The direction of the player.
 * @param p   A pointer to the player struct.
 *
 * @return 0 if the player position is set successfully, 1 if there is a
 * duplicate player error.
 */
int	set_ply_pos(int col, char dir, t_ply *p)
{
	if (p->pos.x >= 0)
		return (1);
	p->pos.y = (double)col;
	if (dir == 'N')
	{
		p->n_dir = (t_point){.x = -1., .y = 0.};
		p->view = (t_point){.x = 0., .y = p->fov};
	}
	else if (dir == 'E')
	{
		p->n_dir = (t_point){.x = 0., .y = 1.};
		p->view = (t_point){.x = p->fov, .y = 0.};
	}
	else if (dir == 'S')
	{
		p->n_dir = (t_point){.x = 1., .y = 0.};
		p->view = (t_point){.x = 0., .y = -p->fov};
	}
	else if (dir == 'W')
	{
		p->n_dir = (t_point){.x = 0., .y = -1.};
		p->view = (t_point){.x = -p->fov, .y = 0.};
	}
	p->p_dir = (t_point){.x = -p->n_dir.y, .y = p->n_dir.x};
	return (0);
}

/**
 * @brief Perform a rotation matrix operation on a given point.
 *
 * This function applies a rotation matrix operation to the given point using
 * the provided sine and cosine values. The rotation matrix formula is used to
 * rotate the player's direction matrix, resulting in a new direction matrix.
 *
 * @param dst  A pointer to the destination point.
 * @param sin_ The sine value for the rotation.
 * @param cos_ The cosine value for the rotation.
 */
static void	rotation_matrix(t_point *dst, double sin_, double cos_)
{
	t_point	buffer;

	buffer = (t_point){.x = dst->x, .y = dst->y};
	dst->x = (buffer.x * cos_) - (buffer.y * sin_);
	dst->y = (buffer.x * sin_) + (buffer.y * cos_);
}

/**
 * @brief Update the player's current position based on movement direction.
 *
 * This function updates the player's current position based on the movement
 * direction specified by the `move` parameter. The player will only move if
 * there is a valid spot to move to on the map. If the spot is either '0' or 'D'
 * (door in open state), the player's position is updated accordingly. Otherwise,
 * the player does not move.
 *
 * @param ply  A pointer to the player's current position.
 * @param move A pointer to the movement direction.
 * @param g    A pointer to the game struct containing important information
 *             like the map.
 * @param dir  The direction of movement (-1 for left or backward, 
 * 1 for right or forward).
 *
 * @return 1 if the player's position is updated, 0 otherwise.
 */
static int	update_move(t_point *ply, const t_point *move, const t_game *g,
		int dir)
{
	double	step_size;
	t_int	update;
	t_int	map_pos;

	update.y = 0;
	step_size = dir * move->x * g->ply.move_speed;
	map_pos = (t_int){(int)(ply->x + 2 * step_size), (int)(ply->y)};
	update.x = get_map_pos(map_pos, &g->map);
	if (update.x == '0' || (update.x == 'D'
			&& get_door_stat(&g->door, map_pos, NULL) == 1))
	{
		ply->x += step_size;
		update.y = 1;
	}
	step_size = dir * move->y * g->ply.move_speed;
	map_pos = (t_int){(int)(ply->x), (int)(ply->y + 2 * step_size)};
	update.x = get_map_pos(map_pos, &g->map);
	if (update.x == '0' || (update.x == 'D'
			&& get_door_stat(&g->door, map_pos, NULL) == 1))
	{
		ply->y += step_size;
		update.y = 1;
	}
	return (update.y);
}

/**
  @brief Updates the player orientation using matrix multiplication.
 *
 * This function updates the player's orientation by applying a rotation matrix
 * based on the given direction. It updates the player's new direction, previous
 * direction, and view direction.
 *
 * @param p A pointer to the player structure.
 * @param dir The direction of rotation (0 for left, 1 for right).
 * @return 1 if the update is successful, 0 otherwise.
 */
static int	update_angle(t_ply *p, int dir)
{
	rotation_matrix(&p->n_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->p_dir, p->rotate_sin[dir], p->rotate_cos[dir]);
	rotation_matrix(&p->view, p->rotate_sin[dir], p->rotate_cos[dir]);
	return (1);
}

/**
 * @brief Update the player's movement and rotation based on the move options.
 *
 * This function updates the player's movement and rotation based on the move
 * options specified in the `p` player struct. It checks each move option bit
 * and calls the corresponding update function. The function returns the total
 * number of updates made to the player's position and orientation.
 *
 * @param p A pointer to the player struct.
 * @param g A pointer to the game struct containing important information.
 *
 * @return The total number of updates made to the player's position and
 *         orientation.
 */
int	update_ply_move(t_ply *p, const t_game *g)
{
	int	update;

	update = 0;
	if (p->move_options & rotate_left)
		update += update_angle(p, 0);
	else if (p->move_options & rotate_right)
		update += update_angle(p, 1);
	if (p->move_options & move_left)
		update += update_move(&p->pos, &p->p_dir, g, 1);
	else if (p->move_options & move_right)
		update += update_move(&p->pos, &p->p_dir, g, -1);
	if (p->move_options & forward)
		update += update_move(&p->pos, &p->n_dir, g, 1);
	else if (p->move_options & backward)
		update += update_move(&p->pos, &p->n_dir, g, -1);
	return (update);
}
