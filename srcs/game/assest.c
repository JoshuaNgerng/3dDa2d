/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:12:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 16:59:02 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
add the information of a sprite into memory
update the no of sprite in memory using max_index member (temporarily will override it later)
*/
void	add_asset(t_asset *a, t_int pos)
{
	a->sprite[a->max_index].status = 0;
	a->sprite[a->max_index].pos = pos;
	a->sprite[a->max_index].counter = 0;
	a->max_index ++;
}

/*
brief
match the given pos to the pos of each spirite in memory
returns the index of the sprite if found, -1 otherwise
*/
int	get_asset_index(const t_asset *a, t_int pos)
{
	int	i;

	i = -1;
	while (++ i < a->len)
	{
		if (a->sprite[i].pos.x == pos.x && a->sprite[i].pos.y == pos.y)
			return (i);
	}
	return (-1);
}

/*
status == 1 and counter == max_index -> door full opened
status == 0 and counter == 0 -> door fully closed
otherwise transitional status
1 -> fully opened
-1 -> full closed
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

/*
if door is near ply
change the status of the door (open or close)
*/
void	update_door(const t_map *m, const t_ply *ply, t_asset *door)
{
	int		index;
	t_int	check;

	check.x = (int)(ply->pos.x);
	check.y = (int)(ply->pos.y);
	if (get_map_pos(check, m) == 'D')
		return ;
	check.x = (int)(ply->pos.x + ply->n_dir.x * 5 * ply->move_speed);
	check.y = (int)(ply->pos.y + ply->n_dir.y * 5 * ply->move_speed);
	if (get_map_pos(check, m) != 'D')
		return ;
	index = get_asset_index(door, check);
	if (index < 0)
		return ;
	door->sprite[index].status ^= 1;
}

/*
update door sprite counter until stable pos is met
status == 1 and counter == max_index -> door full opened
status == 0 and counter == 0 -> door fully closed
otherwise transitional status
*/
void	update_door_counter(t_asset *door)
{
	int	i;
	int	step_dir;

	i = -1;
	step_dir = 1;
	while (++ i < door->len)
	{
		if (door->sprite[i].status
			&& door->sprite[i].counter < door->max_index)
			door->sprite[i].counter += step_dir;
		if (!door->sprite[i].status && door->sprite[i].counter > 0)
			door->sprite[i].counter -= step_dir;
	}
}
