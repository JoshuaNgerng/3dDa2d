/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:58:15 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/24 18:27:39 by jngerng          ###   ########.fr       */
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

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0x0);
	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	return (*((uint32_t *)(img->pixel_ptr + offset)));
}

void	draw_horizontal(t_img *img, t_int range, int row, t_colour c)
{
	while (range.x < range.y)
	{
		change_image_pixel(img, row, range.x, c.trbg);
		range.x ++;
	}
}

void	draw_small_circle(t_img *minimap, const t_game *g)
{
	t_int		range;
	t_int		centre;
	t_colour	yellow;

	centre.x = g->minimap.width / 2;
	centre.y = g->minimap.height / 2;
	yellow = (t_colour){.mode.red = 255, .mode.green = 255};
	change_image_pixel(minimap, centre.x, centre.y, yellow.trbg);
	range = (t_int){centre.y - 2, centre.y + 3};
	draw_horizontal(minimap, range, centre.x, yellow);
	range = (t_int){centre.y - 1, centre.y + 2};
	draw_horizontal(minimap, range, centre.x - 1, yellow);
	draw_horizontal(minimap, range, centre.x + 1, yellow);
	change_image_pixel(minimap, centre.x - 2, centre.y, yellow.trbg);
	change_image_pixel(minimap, centre.x + 2, centre.y, yellow.trbg);
}
