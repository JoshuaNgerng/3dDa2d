/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 17:32:35 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
iterate the entire height of the projected object or till end of screen reached
map the screen img pos to a corresponding pos in texture img
*/
static void	drawing_loop(t_draw *d, const t_ray_fin *obj, int offset)
{
	int	iter;
	double	step_size;
	double	texture_pos;

	iter = -1;
	step_size = 1.0 * d->texture->height / obj->height;
	texture_pos = (d->screen_pos.y - (d->win_height - obj->height) / 2) * step_size;
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

/*
fill the same between back door and front door
doesnt do mapping from texture cause need to adj my raycast algo and im lazy LULZZZZ
*/
static void	drawing_celling_loop(t_draw *d, t_ray_fin *back)
{
	int				iter;
	int				height;
	static t_colour	c = {.mode.red = 48, .mode.green = 25, .mode.blue = 52};

	iter = -1;
	height = (d->win_height - back->height) / 2;
	height -= d->screen_pos.y;
	if (height < 1)
		return ;
	while (++ iter < height && d->screen_pos.y < d->win_height)
	{
		change_image_pixel(d->scene, d->screen_pos.x, d->screen_pos.y, c.trbg);
		d->screen_pos.y ++;
	}
}

/*
draw sky
draw obj
draw floor
*/
void	draw_obj_n_bg(t_img *img, t_ray *r, const t_game *g)
{
	int			iter;
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
	iter = -1;
	while (++ iter < draw.screen_pos.y)
		change_image_pixel(draw.scene, draw.screen_pos.x, iter,
			g->env[sky_].colour.trbg);
	if (ptr->type == door)
		offset = g->door.sprite[ptr->index].counter;
	drawing_loop(&draw, ptr, offset);
	while (draw.screen_pos.y < draw.win_height)
	{
		change_image_pixel(draw.scene, draw.screen_pos.x, draw.screen_pos.y,
			g->env[floor_].colour.trbg);
		draw.screen_pos.y ++;
	}
}

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

void	draw_obj_to_img(t_img *img, t_ray *r, const t_game *g)
{
	r->obj_iter --;
	if (r->obj_iter < 0)
		return ;
	draw_obj_n_bg(img, r, g);
	while (r->obj_iter -- > 0)
		draw_obj(img, r, g);
}
