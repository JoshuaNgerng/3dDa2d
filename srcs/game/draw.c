/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/25 19:08:28 by lchew            ###   ########.fr       */
=======
/*   Updated: 2024/05/29 13:52:59 by jngerng          ###   ########.fr       */
>>>>>>> bonus
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

<<<<<<< HEAD
static const t_img	*fetch_texture(uint8_t type, uint8_t index, const t_game *g)
{
	int	counter;

	if (type == undef)
		return (NULL);
	if (type == wall)
		return (&(g->wall[index]));
	if (type == door_ || type == door)
		return (&(g->door_img));
	counter = 0;
	// counter = (g->key.sprite[index].counter + index) //r->fin[key].index
	// 	% g->key.max_index;
	return (&(g->key_img[counter]));
}

static
void	draw_init(t_ray_fin *obj, t_draw *d, const t_ray *r, const t_game *g)
{
	d->win_height = g->setting.win_height;
	d->env[floor_] = g->env[floor_].colour.trbg;
	d->env[sky_] = g->env[sky_].colour.trbg;
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

=======
/*
iterate the entire height of the projected object or till end of screen reached
map the screen img pos to a corresponding pos in texture img
*/
>>>>>>> bonus
static void	drawing_loop(t_draw *d, const t_ray_fin *obj, int offset)
{
	int	iter;

	iter = -1;
	while (++ iter < obj->height && d->screen_pos.y < d->win_height)
	{
		/* still need to doc this formula LULZ */
		d->texture_pos.y = d->screen_pos.y * 2 - d->win_height + obj->height;
		d->texture_pos.y *= (d->texture->height / 2.) / obj->height;
		/* ** */
		d->texture_pos.y += offset;
		if (d->texture_pos.x < 0)
			printf("newx: %d, y: %d\n", d->texture_pos.x, d->texture_pos.y);
		if (d->texture_pos.y >= d->texture->height)
			break ;
		change_image_pixel(d->scene, d->screen_pos.x, d->screen_pos.y,
			get_image_pixel(d->texture, d->texture_pos.x, d->texture_pos.y));
		d->screen_pos.y ++;
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
<<<<<<< HEAD
}

// void	draw_inner_wall(t_img *img, t_ray *r, const t_game *g)
// {
// 	;
// }
=======
	if (r->fin[r->obj_iter].type != door)
		return ;
	if ((ptr + 1)->type == wall)
		return ;
	drawing_celling_loop(&draw, (ptr + 1));
}
>>>>>>> bonus

void	draw_obj_to_img(t_img *img, t_ray *r, const t_game *g)
{
	r->obj_iter --;
	if (r->obj_iter < 0)
		return ;
	draw_obj_n_bg(img, r, g);
	while (r->obj_iter -- > 0)
<<<<<<< HEAD
	{
		// draw_inner_wall(img, r, g);
		draw_assests(img, r, g);
	}
}

void	draw_key(t_img *img, t_ray *r, const t_game *g)
{
	int		counter;
	t_draw	draw;

	draw.scene = img;
	counter = (g->key.sprite[r->fin[key].index].counter + r->ray_no)
		% g->key.max_index;
	draw.texture = &(g->key_img[counter]);
	if (!(draw.texture->img))
		return ;
	draw.screen_pos.x = r->ray_no;
	draw_init(&r->fin[key], &draw, r, g);
	drawing_loop(&draw, &r->fin[key], 0);
=======
		draw_obj(img, r, g);
>>>>>>> bonus
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
