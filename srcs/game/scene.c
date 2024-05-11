/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/11 17:18:18 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3d.h"

void	change_image_pixel(t_img *img, int x, int y, uint32_t colour)
{
	int	offset;

	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	*((uint32_t *)(img->pixel_ptr + offset)) = colour;
}

uint32_t	get_image_pixel(const t_tex *tex, int x, int y)
{
	int	offset;

	if (x < 0 || x > tex->width || y < 0 || y > tex->height)
		return (0x0);
	offset = (tex->img.line_length * y) + (x * (tex->img.bits_per_pixel / 8));
	return (*((uint32_t *)(tex->img.pixel_ptr + offset)));
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
	put_sky_floor(&g->scene, g, MAX_HEIGHT, MAX_WIDTH);
	put_sky_floor(&g->scene, g, MAX_HEIGHT, MAX_WIDTH);
	raycasting_walls(&g->scene, g);
	// put_minimap(&g->scene, g);
}
