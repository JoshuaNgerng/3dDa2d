/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:18:32 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/24 22:09:21 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
1 -> open
-1 -> close
0 -> transistion / unknown
*/
int	get_door_status(const t_asset *door, t_int pos, int *index_ptr)
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
	if (!door->sprite[index].status
		&& !door->sprite[index].counter)
		return (-1);
	return (0);
}

void	update_door(const t_map *m, const t_ply *ply, t_asset *door)
{
	int		index;
	t_int	check;

	check.x = (int)floor(ply->pos.x + ply->n_dir.x * 5 * ply->move_speed);
	check.y = (int)floor(ply->pos.y + ply->n_dir.y * 5 * ply->move_speed);
	if (get_map_pos(check, m) != 'D')
		return ;
	index = get_asset_index(door, check);
	if (index < 0)
		return ;
	door->sprite[index].status ^= 1;
}

void	update_door_counter(t_asset *door)
{
	int	i;
	int	step_dir;

	i = -1;
	step_dir = 1;
	// printf("step dir test %d\n", step_dir);
	while (++ i < door->len)
	{
		if (door->sprite[i].status
			&& door->sprite[i].counter < door->max_index)
			door->sprite[i].counter += step_dir;
		if (!door->sprite[i].status && door->sprite[i].counter > 0)
			door->sprite[i].counter -= step_dir;
		// printf("index %d, door status %d, counter %d\n",
			// i, door->sprite[i].status, door->sprite[i].counter);
	}
}
