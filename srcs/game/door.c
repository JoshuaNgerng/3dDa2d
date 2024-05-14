/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:18:32 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 17:32:45 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_door_counter(t_game *g)
{
	int	i;

	i = -1;
	while (++ i < g->door.len)
	{
		if (!g->door.sprite[i].status && g->door.sprite[i].counter > 0)
			g->door.sprite[i].counter ++;
		if (g->door.sprite[i].counter == 4)
			g->door.sprite[i].counter = -1;
	}
}