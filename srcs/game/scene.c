/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:58:15 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 09:43:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Changes the color of a pixel in an image.
 *
 * This function modifies the color of a pixel at the specified coordinates (x, y)
 * in the given image.
 *
 * @param img The image to modify.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param colour The new color of the pixel.
 */
void	change_image_pixel(t_img *img, int x, int y, uint32_t colour)
{
	int offset;

	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	*((uint32_t *)(img->pixel_ptr + offset)) = colour;
}

/**
 * @brief Retrieves the pixel value at the specified coordinates from an image.
 *
 * This function takes an image pointer, along with the x and y coordinates of
 * the pixel, and returns the pixel value at that location. If the coordinates
 * are out of bounds, the function returns 0x0.
 *
 * @param img The image from which to retrieve the pixel.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The pixel value at the specified coordinates, or 0x0 if the
 * coordinates are out of bounds.
 */
uint32_t	get_image_pixel(const t_img *img, int x, int y)
{
	int offset;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0x0);
	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	return (*((uint32_t *)(img->pixel_ptr + offset)));
}

/*
draw a hori line in memory t_img
range.x is the starting pos
range.y is the end pos
row is the which row pos in memory
c is the colour to write to memory
*/
void	draw_horizontal(t_img *img, t_int range, int row, t_colour c)
{
	while (range.x < range.y)
	{
		change_image_pixel(img, row, range.x, c.trbg);
		range.x ++;
	}
}

/*
draw a diamon shape in the centre of the minimap to rep the p[lt]
*/
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

void	draw_pointer(t_img *minimap, const t_game *g)
{
	t_point		ply_pos;
	int			pointer_len;
	double		pointer_angle;
	
	pointer_len = 15;
	ply_pos.x = g->minimap.width / 2 + 0.5;
	ply_pos.y = g->minimap.height / 2 + 0.5 ;
	if (g->ply.n_dir.x == -1)
		pointer_angle = 3 * M_PI / 2;
	else if (g->ply.n_dir.x == 1)
		pointer_angle = M_PI / 2;
	else
		pointer_angle = atan2(g->ply.n_dir.x, g->ply.n_dir.y);
	while (pointer_len-- > 0)
	{
		ply_pos.x += cos(pointer_angle);
		ply_pos.y += sin(pointer_angle);
		change_image_pixel(minimap, (int)(ply_pos.x), (int)(ply_pos.y), 
				(t_colour){.mode.green = 255}.trbg);
	}
}
