/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:12:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/24 22:20:12 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_asset(t_asset *a, t_int pos, int counter)
{
	a->sprite[a->max_index].status = 1;
	a->sprite[a->max_index].pos = pos;
	a->sprite[a->max_index].counter = counter;
	a->max_index ++;
}

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

void	update_key(t_map *m, t_asset *key, const t_ply *ply)
{
	int	i;
	int	index;

	i = -1;
	while (++ i < key->len)
	{
		if (!key->sprite[i].status)
			continue ;
		if (key->sprite[i].pos.x == (int)ply->pos.x
			&& key->sprite[i].pos.y == (int)ply->pos.y)
		{
			key->sprite[i].status = 0;
			index = key->sprite[i].pos.x * m->width + key->sprite[i].pos.y;
			m->map[index] = '0';
		}
		key->sprite[i].counter ++;
		if (key->sprite[i].counter == key->max_index)
			key->sprite[i].counter = 0;
	}
}
