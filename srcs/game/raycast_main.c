/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/08 14:37:22 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_wall(t_img *img, int ray_no, t_ray *r, const t_game *g)
{
	int		iter;
	t_int	screen_pos;
	t_int	texture_pos;
	int		height;
	const t_tex	*ptr;

	ptr = &(g->wall[r->side]);
	if (!(ptr->img.img))
		return ;
	height = (int)fabs(g->setting.win_height / r->perp_dist);
	r->hitpoint -= floor(r->hitpoint);
	texture_pos.x = (int)(r->hitpoint * ptr->width);
	if (r->side > vertical && r->ray_dir.y < 0.)
		texture_pos.x = ptr->width - texture_pos.x - 1;
	else if (r->side <= vertical && r->ray_dir.x > 0.)
		texture_pos.x = ptr->width - texture_pos.x - 1;
	screen_pos = (t_int){.x = ray_no, .y = (g->setting.win_height - height) / 2};
	if (screen_pos.y < 0)
		screen_pos.y = 0;
	iter = -1;
	while (++ iter < height && screen_pos.y < g->setting.win_height)
	{
		texture_pos.y = (screen_pos.y * 2 - g->setting.win_height + height) *
						((ptr->height / 2.) / height);
		change_image_pixel(img, screen_pos.x, screen_pos.y, get_image_pixel(ptr, texture_pos.x, texture_pos.y));
		screen_pos.y ++;
	}
}

void	draw_red_wall(t_img *img, int ray_no, t_ray *r, const t_game *g)
{
	int			iter;
	t_colour	test;
	double height;
	int	start;
	int	end;

	height = fabs(g->setting.win_height / r->perp_dist);
	start = (g->setting.win_height - height) / 2;
	if (start < 0)
		start = 0;
	end = (height + g->setting.win_height) / 2;
	if (end >= g->setting.win_height)
		end = g->setting.win_height - 1;
	// printf("testing height huh %d\n", (int)r->height);
	test.mode = (t_trbg){.red = 255};
	iter = start - 1;
	while (++ iter < end)
		change_image_pixel(img, ray_no, iter, test.trbg);
}

void	raycasting_walls(t_img *img, const t_game *g)
{
	t_ray	ray;
	int		ray_no;

	ray_no = -1;
	while (++ ray_no < g->setting.win_width)
	{
		if (raycast_loop(&ray, ray_no, g))
			continue ;
		draw_wall(img, ray_no, &ray, g);
		// draw_red_wall(img, ray_no, &ray, g);
	}
}
