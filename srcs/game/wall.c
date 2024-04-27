/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:21:39 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/05 15:35:44 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
/*
int	calculate_wall(t_ray_fin *fin, t_ray_fin *h, t_ray_fin *v, double angle)
{
	if (v->dist < h->dist)
	{
		fin->ray_x = v->ray_x;
		fin->ray_y = v->ray_y;
		fin->dist = v->dist;
		if (angle > M_PI_2 && angle < M_PI_4 * 3)
			return (0);
		return (2);
	}
	fin->ray_x = h->ray_x;
	fin->ray_y = h->ray_y;
	fin->dist = h->dist;
	if (angle > 0 && angle < M_PI_2)
		return (3);
	return (1);
}

static void	test_draw_red_wall(t_img *img, int ray_no, double height, double off)
{
	int			width;
	int			pos;
	t_colour	c;

	c.trabg_parts[0] = 0;
	c.trabg_parts[1] = 0;
	c.trabg_parts[2] = 255;
	c.trabg_parts[3] = 0;
	width = -1;
	while (++ width < 20)
	{
		pos = -1;
		if (height < 1)
			printf("empty\n");
		while (++ pos < height)
			change_image_pixel(img, ray_no * 20 + width, (int)off + pos, c.trbg);
	}
}

void	draw_wall(t_ray_fin *fin, const t_ray *r, int counter, t_game *g)
{
	double	angle_diff;
	double	height;
	// double	height_off;
	double	offset;
	(void) counter;

	new_angle(&angle_diff, g->ply.view - r->angle);
	fin->dist *= cos(angle_diff);
	height = MAX_HEIGTH / fin->dist;
	if (height > MAX_HEIGTH)
		height = MAX_HEIGTH;
	offset = (MAX_HEIGTH - height) / 2;
	printf("test offest val %lf\n", offset);
	// printf("test height %d fin dist %lf\n", (int)height, fin->dist);
	test_draw_red_wall(&g->scene, r->no_ray, height, offset);
}
*/

static void	test_draw_red_wall(t_game *g, int ray_no, double dist)
{
	int			width;
	int			pos;
	int			height;
	int			offset;
	t_colour	c;

	c.trabg_parts[0] = 0;
	c.trabg_parts[1] = 0;
	c.trabg_parts[2] = 255;
	c.trabg_parts[3] = 0;
	height = MAX_HEIGTH / dist;
	if (height > MAX_HEIGTH)
		height = MAX_HEIGTH;
	offset = (MAX_HEIGTH - height) / 2;
	width = -1;
	// printf("draw wall at %d(%d)(%lf) (%d)\n", ray_no, height, dist, g->setting.wall_strip_width);
	while (++ width < g->setting.wall_strip_width - 2)
	{
		pos = -1;
		// printf("test crash %d %d height(%d) off(%d) dist(%lf)\n", ray_no * g->setting.wall_strip_width + width, offset + pos, height, offset, dist);
		while (++ pos < height)
			change_image_pixel(&g->scene,
			ray_no * g->setting.wall_strip_width + width, offset + pos, c.trbg);
	}
}

static const t_tex	*get_texture(const t_game *g, char type, double angle)
{
	if (angle >= 0 & angle < _2_M_PI)
	{
		if (type == 'h')
			return (&g->wall[0]);
		if (angle >= 0 && angle < M_PI)
			return (&g->wall[3]);
		return (&g->wall[1]);
	}
	if (type == 'h')
		return (&g->wall[2]);
	if (angle >= M_PI && angle < M_PI_2 * 3)
		return (&g->wall[1]);
	return (&g->wall[3]);
}

static uint32_t	get_colour_pixel(const t_tex *wall, int row, int col)
{
	(void)wall;
	(void)row;
	(void)col;
	return (0);
}

static void	map_wall_texture_to_image(const t_tex *wall, t_game *g, const t_ray_dist *r, int ray_no)
{
	int		width;
	int		pos;
	int		height;
	int		offset;
	int		strip;
	double	ratio_width;

	return ;
	height = MAX_HEIGTH / r->dist;
	if (height > MAX_HEIGTH)
		height = MAX_HEIGTH;
	offset = (MAX_HEIGTH - height) / 2;
	width = -1;
	ratio_width = modf(((r->type == 'h') ? (r->ray_x) : (r->ray_y)), &ratio_width) * wall->width;
	strip = ray_no * g->setting.wall_strip_width;
	while (++ width < g->setting.wall_strip_width)
	{
		pos = -1;
		while (++ pos < height - 1)
		{
			change_image_pixel(&g->scene, strip + width, offset + pos,
				get_colour_pixel(wall, (int)ratio_width, (int)((pos + 1) * wall->height / height)));
		}
	}
}

void	draw_wall(t_game *g, const t_ray_dist *r, int ray_no, double angle)
{
	const t_tex	*ptr;

	if (r->dist < 0)
	{
		printf("huh\n");
		return ;
	}
	test_draw_red_wall(g, ray_no, r->dist);
	return ;
	ptr = get_texture(g, r->type, angle);
	map_wall_texture_to_image(ptr, g, r, ray_no);
	// test_draw_red_wall(g, ray_no, r->dist);
}
