/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/16 17:27:24 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_init(t_ray *r, t_draw *d, int type, const t_game *g)
{
	r->fin[type].hitpoint -= floor(r->fin[type].hitpoint);
	r->fin[type].height = (int)fabs(g->setting.win_height / r->fin[type].perp_dist);
	d->texture_pos.x = (int)(r->fin[type].hitpoint * d->texture->width);
	if (r->side > vertical && r->ray_dir.y < 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	else if (r->side <= vertical && r->ray_dir.x > 0.)
		d->texture_pos.x = d->texture->width - d->texture_pos.x - 1;
	d->screen_pos.y = (g->setting.win_height - r->fin[type].height) / 2;
	if (d->screen_pos.y < 0)
		d->screen_pos.y = 0;
}

void	draw_wall(t_img *img, t_ray *r, const t_game *g)
{
	int		iter;
	int		win_height;
	t_draw	draw;

	draw.texture = &(g->wall[r->side]);
	if (r->fin[wall].type == door)
		draw.texture = &(g->door_img);
	if (!(draw.texture->img))
		return ;
	win_height = g->setting.win_height;
	draw.screen_pos.x = r->ray_no;
	draw_init(r, &draw, wall, g);
	iter = -1;
	while (++ iter < r->fin[wall].height && draw.screen_pos.y < win_height)
	{
		draw.texture_pos.y = draw.screen_pos.y * 2 - win_height + r->fin[wall].height;
		draw.texture_pos.y *= ((draw.texture->height / 2.) / r->fin[wall].height);
		change_image_pixel(img, draw.screen_pos.x, draw.screen_pos.y,
			get_image_pixel(draw.texture, draw.texture_pos.x, draw.texture_pos.y));
		draw.screen_pos.y ++;
	}
}

void	draw_door(t_img *img, t_ray *r, const t_game *g)
{
	int		iter;
	int		win_height;
	t_draw	draw;

	if (r->fin[door].type == undef)
		return ;
	draw.texture = &(g->door_img);
	if (!(draw.texture->img))
		return ;
	win_height = g->setting.win_height;
	draw.screen_pos.x = r->ray_no;
	draw_init(r, &draw, wall, g);
	iter = -1;
	while (++ iter < r->fin[wall].height && draw.screen_pos.y < win_height)
	{
		draw.texture_pos.y = draw.screen_pos.y * 2 - win_height + r->fin[wall].height;
		draw.texture_pos.y *= ((draw.texture->height / 2.) / r->fin[wall].height);
		draw.texture_pos.y += g->key.sprite->counter;
		if (draw.texture_pos.y > draw.texture->height)
			break ;
		change_image_pixel(img, draw.screen_pos.x, draw.screen_pos.y,
			get_image_pixel(draw.texture, draw.texture_pos.x, draw.texture_pos.y));
		draw.screen_pos.y ++;
	}
}

void	draw_key(t_img *img, t_ray *r, const t_game *g)
{
	if (r->fin[key].type == undef)
		return ;
}

void	raycasting_walls(t_img *img, const t_game *g)
{
	t_ray	ray;

	ray.ray_no = -1;
	while (++ ray.ray_no < g->setting.win_width)
	{
		if (raycast_loop(&ray, g))
		{
			draw_door(img, &ray, g);
			draw_key(img, &ray, g);
			continue ;
		}
		draw_wall(img, &ray, g);
		draw_door(img, &ray, g);
		draw_key(img, &ray, g);
	}
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
