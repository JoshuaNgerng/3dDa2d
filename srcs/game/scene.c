/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:58:15 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/20 16:16:31 by jngerng          ###   ########.fr       */
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

void	empty_minimap_init(t_img *minimap, const t_game *g)
{
	t_colour	border;
	t_int		iter;

	iter.y = -1;
	border = (t_colour){.mode.transparency = 200, .mode.red = 255};
	while (++ iter.y < g->minimap_info.padding_y)
	{
		iter.x = -1;
		while (++ iter.x < g->minimap.width)
		{
			// printf("0 x %d , y %d\n", iter.x, iter.y);
			change_image_pixel(minimap, iter.x, iter.y, border.trbg);
		}
	}
	while (iter.y < g->minimap.height - g->minimap_info.padding_y)
	{
		iter.x = -1;
		while (++ iter.x < g->minimap_info.padding_x)
		{
			// printf("1 x %d , y %d\n", iter.x, iter.y);
			change_image_pixel(minimap, iter.x, iter.y, border.trbg);
		}
		iter.x = g->minimap.width - g->minimap_info.padding_x - 1;
		while (++ iter.x < g->minimap.width)
		{
			// printf("1 x %d , y %d\n", iter.x, iter.y);
			change_image_pixel(minimap, iter.x, iter.y, border.trbg);
		}
		iter.y ++;
	}
	while (iter.y < g->minimap.height)
	{
		iter.x = -1;
		while (++ iter.x < g->minimap.width)
		{
			// printf("2 x %d , y %d\n", iter.x, iter.y);
			change_image_pixel(minimap, iter.x, iter.y, border.trbg);
		}
		iter.y ++;
	}
}

void	refresh_minimap(t_img *minimap, const t_game *g)
{
	t_int		iter;

	iter.x = g->minimap_info.padding_x;
	while (++ iter.x < g->minimap.width - g->minimap_info.padding_x)
	{
		iter.y = g->minimap_info.padding_y;
		while (++ iter.y < g->minimap.height - g->minimap_info.padding_y)
		{
			// printf("3 x %d , y %d\n", iter.x, iter.y);
			change_image_pixel(minimap, iter.x, iter.y, g->minimap_info.block_colour[1].trbg);
		}
	}
}
