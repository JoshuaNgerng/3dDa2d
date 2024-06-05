/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:49:21 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 18:22:34 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Initializes the necessary variables for drawing objects.
 *
 * This function initializes the necessary variables for drawing objects. It
 * checks the type of the object and assigns the appropriate texture. It
 * calculates the height of the object based on the window height and the
 * perpendicular distance. It calculates the texture position based on the
 * hitpoint and the texture width. It adjusts the texture position based on the
 * side and ray direction. It calculates the screen position based on the ray
 * number and the object height. Finally, it ensures that the screen position is
 * not negative.
 *
 * @param obj The object information.
 * @param d The drawing information.
 * @param r The ray information.
 * @param g The game information.
 */
void	draw_flip_init(t_ray_fin *obj, t_draw *d, const t_ray *r, \
	const t_game *g)
{
	d->texture = NULL;
	if (obj->type == undef)
		return ;
	if (obj->type == wall)
		d->texture = &(g->wall[obj->side]);
	else if (obj->type == door_)
		d->texture = &(g->door_img[1]);
	else
		d->texture = g->door_img;
	d->win_height = g->setting.win_height;
	obj->hitpoint -= floor(obj->hitpoint);
	obj->height = (int)fabs(g->setting.win_height / obj->perp_dist);
	d->texture_pos.x = (int)(obj->hitpoint * d->texture->width);
	if ((obj->side == north || obj->side == south) && r->ray_dir.y < 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	else if ((obj->side == west || obj->side == east) && r->ray_dir.x > 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	d->screen_pos.x = r->ray_no;
	d->screen_pos.y = (g->setting.win_height - obj->height) / 2;
	if (d->screen_pos.y < 0)
		d->screen_pos.y = 0;
}

/**
 * @brief Initializes the necessary variables for drawing objects.
 *
 * This function initializes the necessary variables for drawing objects. It
 * checks the type of the object and assigns the appropriate texture. It
 * calculates the height of the object based on the window height and the
 * perpendicular distance. It calculates the texture position based on the
 * hitpoint and the texture width. It adjusts the texture position based on the
 * side and ray direction. It calculates the screen position based on the ray
 * number and the object height. Finally, it ensures that the screen position is
 * not negative.
 *
 * @param obj The object information.
 * @param d The drawing information.
 * @param r The ray information.
 * @param g The game information.
 */
void	draw_init(t_ray_fin *obj, t_draw *d, const t_ray *r, const t_game *g)
{
	d->texture = NULL;
	if (obj->type == undef)
		return ;
	if (obj->type == wall)
		d->texture = &(g->wall[obj->side]);
	else if (obj->type == door_)
		d->texture = &(g->door_img[1]);
	else
		d->texture = g->door_img;
	d->win_height = g->setting.win_height;
	obj->hitpoint -= floor(obj->hitpoint);
	obj->height = (int)fabs(g->setting.win_height / obj->perp_dist);
	d->texture_pos.x = (int)(obj->hitpoint * d->texture->width);
	if ((obj->side == north || obj->side == south) && r->ray_dir.x < 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	else if ((obj->side == west || obj->side == east) && r->ray_dir.y > 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	d->screen_pos.x = r->ray_no;
	d->screen_pos.y = (g->setting.win_height - obj->height) / 2;
	if (d->screen_pos.y < 0)
		d->screen_pos.y = 0;
}

/**
 * @brief Draws objects and background on the screen.
 *
 * This function is responsible for drawing objects and background on the screen.
 * It takes an image, a ray, and the game state as parameters. It initializes the
 * necessary variables and checks if the texture is available. It then draws the
 * sky, followed by the objects using a drawing loop. 
 * 
 * Finally, it draws the floor.
 *
 * @param img The image to draw on.
 * @param r The ray containing the information about the objects to draw.
 * @param g The game state.
 */
void	draw_obj_n_bg(t_img *img, t_ray *r, const t_game *g)
{
	int			offset;
	t_ray_fin	*ptr;
	t_draw		draw;

	offset = 0;
	draw.scene = img;
	ptr = &(r->fin[r->obj_iter]);
	if (ptr->type == door)
		draw_flip_init(ptr, &draw, r, g);
	else
		draw_init(ptr, &draw, r, g);
	if (!(draw.texture) || !(draw.texture->img))
		return ;
	draw_sky(&draw, g);
	if (ptr->type == door)
		offset = g->door.sprite[ptr->index].counter;
	drawing_loop(&draw, ptr, offset);
	draw_floor(&draw, g);
}

/**
 * @brief Draws objects to the image based on the ray and game information.
 *
 * This function is responsible for drawing objects to the image using the given
 * ray and game information. It decrements the object iterator and checks if it
 * is less than zero. If so, it returns. Otherwise, it calls the function
 * draw_obj_n_bg() to draw the objects and background, and then iterates through
 * the remaining objects and calls the function draw_obj() to draw each object.
 *
 * @param img The image to draw the objects on.
 * @param r The ray information.
 * @param g The game information.
 */
void	draw_obj(t_img *img, t_ray *r, const t_game *g)
{
	int			offset;
	t_ray_fin	*ptr;
	t_draw		draw;

	offset = 0;
	draw.scene = img;
	ptr = &(r->fin[r->obj_iter]);
	if (ptr->type == door)
		draw_flip_init(ptr, &draw, r, g);
	else
		draw_init(ptr, &draw, r, g);
	if (!(draw.texture) || !(draw.texture->img))
		return ;
	if (ptr->type == door || ptr->type == door_)
		offset = g->door.sprite[ptr->index].counter;
	drawing_loop(&draw, ptr, offset);
	if (r->fin[r->obj_iter].type != door)
		return ;
	if (r->obj_iter + 1 == MAX_RENDER_OBJ)
		return ;
	drawing_celling_loop(&draw, (ptr + 1));
}

/**
 * @brief Draws objects to the image based on the ray and game information.
 *
 * This function is responsible for drawing objects to the image using the given
 * ray and game information. It decrements the object iterator and checks if it
 * is less than zero. If so, it returns. Otherwise, it calls the function
 * draw_obj_n_bg() to draw the objects and background, and then iterates through
 * the remaining objects and calls the function draw_obj() to draw each object.
 *
 * @param img The image to draw the objects on.
 * @param r The ray information.
 * @param g The game information.
 */
void	draw_obj_to_img(t_img *img, t_ray *r, const t_game *g)
{
	r->obj_iter--;
	if (r->obj_iter < 0)
		return ;
	draw_obj_n_bg(img, r, g);
	while (r->obj_iter-- > 0)
		draw_obj(img, r, g);
}
