/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:58:15 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/16 14:11:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	change_image_pixel(t_img *img, int x, int y, uint32_t colour)
{
	int	offset;

	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	*((uint32_t *)(img->pixel_ptr + offset)) = colour;
}

uint32_t	get_image_pixel(const t_img *img, int x, int y)
{
	int	offset;

	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return (0x0);
	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	return (*((uint32_t *)(img->pixel_ptr + offset)));
}

void	put_sky_floor(t_img *scene, const t_game *g, int height, int width)
{
	int	row;
	int	col;

	row = -1;
	while (++ row < height / 2)
	{
		col = -1;
		while (++ col < width)
			change_image_pixel(scene, col, row, g->env[1].colour.trbg);
	}
	while (row < height)
	{
		col = -1;
		while (++ col < width)
			change_image_pixel(scene, col, row, g->env[0].colour.trbg);
		row ++;
	}
}

/*
put sky and floor
then read map and player view to raycast walls
put overrwrite bg with walls
(bonus) overlay with more transparency a small mini win with view
*/
void	generate_scene(t_game *g)
{
	put_sky_floor(&g->scene, g, g->setting.win_height, g->setting.win_width);
	raycasting_walls(&g->scene, g);
}
