/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 18:02:04 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


/**
 * @brief The drawing loop function is responsible for drawing a portion of
 *        the object on the screen based on the given ray information.
 *
 * This function iterates over the height of the object and the screen position,
 * and calculates the texture position based on the screen position and the
 * object height. It then checks if the texture position is within the bounds
 * of the texture image. If it is, it changes the corresponding pixel on the
 * scene image using the pixel from the texture image. Finally, it increments
 * the screen position.
 *
 * @param d The draw structure containing the information for drawing.
 * @param obj The ray information of the object being drawn.
 * @param offset The offset value for the texture position.
 */
void	drawing_loop(t_draw *d, const t_ray_fin *obj, int offset)
{
	int		iter;
	double	step_size;
	double	texture_pos;

	iter = -1;
	step_size = 1.0 * d->texture->height / obj->height;
	texture_pos = (d->screen_pos.y - (d->win_height - obj->height) / 2) \
		* step_size;
	while (++ iter < obj->height && d->screen_pos.y < d->win_height)
	{
		d->texture_pos.y = (int)(texture_pos) & (d->texture->height - 1);
		d->texture_pos.y += offset;
		if (d->texture_pos.y >= d->texture->height)
			break ;
		change_image_pixel(d->scene, d->screen_pos.x, d->screen_pos.y,
			get_image_pixel(d->texture, d->texture_pos.x, d->texture_pos.y));
		d->screen_pos.y ++;
		texture_pos += step_size;
	}
}

/**
 * @brief Draws the ceiling of the game screen.
 *
 * This function is responsible for drawing the ceiling of the game screen.
 * It calculates the height of the ceiling based on the window height and the
 * height of the wall. It then iterates over the height and changes the
 * corresponding pixels on the scene image to the specified color.
 *
 * @param d The draw structure containing the information for drawing.
 * @param back The ray_fin structure containing the height of the wall.
 */
void	drawing_celling_loop(t_draw *d, t_ray_fin *back)
{
	int				iter;
	int				height;
	static t_colour	c = {.mode.red = 48, .mode.green = 25, .mode.blue = 52};

	iter = -1;
	height = (d->win_height - back->height) / 2;
	height -= d->screen_pos.y;
	if (height < 1)
		return ;
	while (++iter < height && d->screen_pos.y < d->win_height)
	{
		change_image_pixel(d->scene, d->screen_pos.x, d->screen_pos.y, c.trbg);
		d->screen_pos.y++;
	}
}


/**
 * @brief Draws the sky of the game screen.
 *
 * This function is responsible for drawing the sky of the game screen.
 * It iterates over the screen position and changes the corresponding pixels
 * on the scene image to the specified color from the sky environment.
 *
 * @param draw The draw structure containing the information for drawing.
 * @param r The ray information for the current frame.
 * @param g The game structure containing the environment information.
 */
void	draw_sky(t_draw *draw, const t_game *g)
{
	int	iter;

	iter = -1;
	while (++iter < draw->screen_pos.y)
	{
		change_image_pixel(draw->scene, draw->screen_pos.x, iter,
			g->env[sky_].colour.trbg);
	}
}


/**
 * @brief Draws the floor of the game screen.
 *
 * This function is responsible for drawing the floor of the game screen.
 * It iterates over the screen position and changes the corresponding pixels
 * on the scene image to the specified color from the floor environment.
 *
 * @param draw The draw structure containing the information for drawing.
 * @param g The game structure containing the environment information.
 */
void	draw_floor(t_draw *draw, const t_game *g)
{
	while (draw->screen_pos.y < draw->win_height)
	{
		change_image_pixel(draw->scene, draw->screen_pos.x, draw->screen_pos.y,
			g->env[floor_].colour.trbg);
		draw->screen_pos.y++;
	}
}

