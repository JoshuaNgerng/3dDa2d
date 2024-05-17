/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/17 16:20:38 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_init(t_ray_fin *object, t_draw *d, const t_ray *r, const t_game *g)
{
	d->win_height = g->setting.win_height;
	d->env[floor_] = g->env[floor_].colour.trbg;
	d->env[sky_] = g->env[sky_].colour.trbg;
	object->hitpoint -= floor(object->hitpoint);
	object->height = (int)fabs(g->setting.win_height / object->perp_dist);
	d->texture_pos.x = (int)(object->hitpoint * d->texture->width);
	if ((object->side == north || object->side == south) && r->ray_dir.y < 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	else if ((object->side == west || object->side == east) && r->ray_dir.x > 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	d->screen_pos.y = (g->setting.win_height - object->height) / 2;
	if (d->screen_pos.y < 0)
		d->screen_pos.y = 0;
}

static void	drawing_loop(t_draw *d, const t_ray_fin *object, int offset)
{
	int	iter;

	iter = -1;
	while (++ iter < object->height && d->screen_pos.y < d->win_height)
	{
		d->texture_pos.y = d->screen_pos.y * 2 - d->win_height + object->height;
		d->texture_pos.y *= ((d->texture->height / 2.) / object->height);
		d->texture_pos.y += offset;
		if (d->texture_pos.y > d->texture->height)
			break ;
		change_image_pixel(d->scene, d->screen_pos.x, d->screen_pos.y,
			get_image_pixel(d->texture, d->texture_pos.x, d->texture_pos.y));
		d->screen_pos.y ++;
	}
}

void	draw_wall(t_img *img, t_ray *r, const t_game *g)
{
	int		iter;
	t_draw	draw;

	draw.scene = img;
	draw.texture = &(g->wall[r->side]);
	if (r->fin[wall].type == door)
		draw.texture = &(g->door_img);
	if (!(draw.texture->img))
		return ;
	draw.screen_pos.x = r->ray_no;
	draw_init(&r->fin[wall], &draw, r, g);
	iter = -1;
	while (++ iter < draw.screen_pos.y)
		change_image_pixel(draw.scene, draw.screen_pos.x, iter, draw.env[sky_]);
	drawing_loop(&draw, &r->fin[wall], 0);
	while (draw.screen_pos.y < draw.win_height)
	{
		change_image_pixel(draw.scene, draw.screen_pos.x, draw.screen_pos.y, draw.env[floor_]);
		draw.screen_pos.y ++;
	}
}

void	draw_door(t_img *img, t_ray *r, const t_game *g)
{
	t_draw	draw;

	if (r->fin[door].type == undef)
		return ;
	draw.scene = img;
	draw.texture = &(g->door_img);
	if (!(draw.texture->img))
		return ;
	draw.screen_pos.x = r->ray_no;
	draw_init(&r->fin[door], &draw, r, g);
	drawing_loop(&draw, &r->fin[door], g->key.sprite->counter);
}

void	draw_key(t_img *img, t_ray *r, const t_game *g)
{
	int		counter;
	t_draw	draw;

	if (r->fin[key].type == undef)
		return ;
	draw.scene = img;
	counter = (g->key.sprite[r->fin[key].index].counter + r->ray_no)
		% g->key.max_index;
	draw.texture = &(g->key_img[counter]);
	if (!(draw.texture->img))
		return ;
	draw.screen_pos.x = r->ray_no;
	draw_init(&r->fin[key], &draw, r, g);
	drawing_loop(&draw, &r->fin[key], 0);
}

/*
void	draw_red_wall(t_img *img, int ray_no, t_ray *r, const t_game *g)
{
	int			iter;
	t_colour	test;
	double		height;
	int			start;
	int			end;

	height = fabs(g->setting.win_height / r->perp_dist);
	start = (g->setting.win_height - height) / 2;
	if (start < 0)
		start = 0;
	end = (height + g->setting.win_height) / 2;
	if (end >= g->setting.win_height)
		end = g->setting.win_height - 1;
	test.mode = (t_trbg){.red = 255};
	iter = start - 1;
	while (++ iter < end)
		change_image_pixel(img, ray_no, iter, test.trbg);
}
*/
