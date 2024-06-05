/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:12:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 18:21:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Add the information of a sprite into memory and update the number of
 *        sprites in memory using the max_index member (temporarily, will be
 *        overridden later).
 *
 * @param a The asset structure to add the sprite to.
 * @param pos The position of the sprite.
 */
void	add_asset(t_asset *a, t_int pos)
{
	a->sprite[a->max_index].status = 0;
	a->sprite[a->max_index].pos = pos;
	a->sprite[a->max_index].counter = 0;
	a->max_index++;
}

/**
 * @brief Match the given position to the position of each sprite in memory.
 *
 * @param a The asset structure to search in.
 * @param pos The position to match.
 * @return The index of the sprite if found, -1 otherwise.
 */
int	get_asset_index(const t_asset *a, t_int pos)
{
	int	i;

	i = -1;
	while (++i < a->len)
	{
		if (a->sprite[i].pos.x == pos.x && a->sprite[i].pos.y == pos.y)
			return (i);
	}
	return (-1);
}

/**
 * @brief Get the status of a door based on its position in the asset structure.
 *
 * The status of a door can be one of the following:
 * - 1: Fully opened
 * - -1: Fully closed
 * - 0: Transitional/unknown
 *
 * @param door The asset structure containing the door sprites.
 * @param pos The position of the door.
 * @param index_ptr A pointer to store the index of the door sprite.
 * @return The status of the door.
 */
int	get_door_stat(const t_asset *door, t_int pos, int *index_ptr)
{
	int	index;

	index = get_asset_index(door, pos);
	if (index < 0)
		return (0);
	if (index_ptr)
		*index_ptr = index;
	if (door->sprite[index].status
		&& door->sprite[index].counter == door->max_index)
		return (1);
	if (!door->sprite[index].status && !door->sprite[index].counter)
		return (-1);
	return (0);
}

/**
 * @brief Update the status of a door based on the player's position.
 *
 * If the door is near the player, change its status (open or close).
 *
 * @param m The map structure.
 * @param ply The player structure.
 * @param door The asset structure containing the door sprites.
 */
void	update_door(const t_map *m, const t_ply *ply, t_asset *door)
{
	int		index;
	t_int	check;

	check.x = (int)(ply->pos.x + ply->n_dir.x * 5 * ply->move_speed);
	check.y = (int)(ply->pos.y + ply->n_dir.y * 5 * ply->move_speed);
	if (check.x == (int)(ply->pos.x) && check.y == (int)(ply->pos.y))
		return ;
	if (get_map_pos(check, m) != 'D')
		return ;
	index = get_asset_index(door, check);
	if (index < 0)
		return ;
	door->sprite[index].status ^= 1;
}

/**
 * @brief Update the counter of door sprites until a stable position is reached.
 *
 * @note The counter represents the progress of the door's movement:
 * @note - If status is 1 and counter is equal to max_index, the door is fully
 * @note   opened.
 * @note - If status is 0 and counter is 0, the door is fully closed.
 * @note - Otherwise, the door is in a transitional state.
 * 
 * @param door The asset structure containing the door sprites.
 */
void	update_door_counter(t_asset *door)
{
	int	i;
	int	step_dir;

	i = -1;
	step_dir = 1;
	while (++i < door->len)
	{
		if (door->sprite[i].status && door->sprite[i].counter < door->max_index)
			door->sprite[i].counter += step_dir;
		if (!door->sprite[i].status && door->sprite[i].counter > 0)
			door->sprite[i].counter -= step_dir;
	}
}
