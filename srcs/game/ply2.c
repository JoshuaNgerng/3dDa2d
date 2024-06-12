/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:46:59 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/12 13:18:57 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Zoom in or out the player's view depending on the dir given.
 *
 * This function adjust the fov of the player by 10 degrees
 * It checks for the fov limits and does not apply changes if the new 
 * fov is outside those limits.
 * It changes fov by scaling the view vector up or down
 * Then change the factor such that the wall in the view would remain the same
 * and not be squashed or elongated
 *
 * @param dst  A pointer to the player struct.
 * @param dir  1 means zoom in -1 means zoom out
 * 
 * @return 1 if the player's fov is updated, 0 otherwise.
 */
int	zoom_fov(t_ply *p, int dir)
{
	int		fov;
	int		check;
	double	factor;

	fov = (int)(p->fov * 90);
	check = fov + dir * 10;
	if (check < 30 || check > 120)
		return (0);
	factor = (double)((double)check / (double)fov);
	p->view.x *= factor;
	p->view.y *= factor;
	p->factor /= factor;
	p->fov = (double)((double)check / 90);
	return (1);
}
