/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:49:21 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/28 11:57:06 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_flip_init(t_ray_fin *obj, t_draw *d, const t_ray *r, const t_game *g)
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
	else if ((obj->side == west || obj->side == east)
			&& r->ray_dir.x > 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	d->screen_pos.x = r->ray_no;
	d->screen_pos.y = (g->setting.win_height - obj->height) / 2;
	if (d->screen_pos.y < 0)
		d->screen_pos.y = 0;
}

/*
init the info needed to determine the projection of the obj
where the obj starts and end on the screen
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
	else if ((obj->side == west || obj->side == east)
			&& r->ray_dir.y > 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	d->screen_pos.x = r->ray_no;
	d->screen_pos.y = (g->setting.win_height - obj->height) / 2;
	if (d->screen_pos.y < 0)
		d->screen_pos.y = 0;
}
