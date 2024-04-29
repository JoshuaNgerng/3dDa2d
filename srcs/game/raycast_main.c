/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:26:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/29 17:12:37 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_wall(t_img *img, int ray_no, t_ray *r, const t_game *g)
{
	int			iter;
	t_colour	test;
	int 		offset;

	if (r->height > g->setting.win_height)
		r->height = g->setting.win_height - 1;
	test.mode = (t_trbg){.red = 255};
	offset = (g->setting.win_height - r->height) / 2;
	printf("testing height huh %d\n", (int)r->height);
	iter = -1;
	while (++ iter < (int)r->height)
		change_image_pixel(img, ray_no, iter + offset, test.trbg);
}

void	raycasting_walls(t_img *img, const t_game *g)
{
	t_ray	ray;
	int		ray_no;

	ray_no = -1;
	while (++ ray_no < g->setting.win_width)
	{
		if (raycast_loop(&ray, ray_no, g))
		{
			printf("ded\n");
			continue ;
		}
		draw_wall(img, ray_no, &ray, g);
	}
}
