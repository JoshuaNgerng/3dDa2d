/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:05:00 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/27 15:29:08 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	change_image_pixel(t_img *img, int x, int y, unsigned int colour)
{
	int	offset;

	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(img->pixel_ptr + offset)) = colour;
}

void	put_sky_floor(t_img *scene, const t_game *g, int height, int width)
{
	int	row;
	int	col;

	row = -1;
	// printf("test sky %x\n", g->env[1].colour.trbg);
	while (++ row < height / 2)
	{
		col = -1;
		while (++ col < width)
			change_image_pixel(scene, col, row, g->env[1].colour.trbg);
	}
	// printf("test floor %x\n", g->env[0].colour.trbg);
	while (row < height)
	{
		col = -1;
		while (++ col < width)
			change_image_pixel(scene, col, row, g->env[0].colour.trbg);
		row ++;
	}
}

// put sky and floor
// then read map and player view to raycast walls
// put overrwrite bg with walls
// (bonus) overlay with more transparency a small mini win with view
void	generate_scene(t_game *g)
{
	put_sky_floor(&g->scene, g, MAX_HEIGTH, MAX_WIDTH);
	raycasting_walls(&g->scene, g);
	// put_minimap(&g->scene, g);
}
