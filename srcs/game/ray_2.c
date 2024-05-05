/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:59:14 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/05 17:38:06 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int	check_wall(char **map, double row, double col)
// {
// 	if ()
// }

void	raycasting_walls(t_game *g)
{
	// static int	i;
	t_ray		ray;
	int			step;
	double		height;

	ray.no_ray = -1;
	height = 0;
	new_angle(&ray.angle, g->ply.view - g->setting.angle_start);
	while (++ ray.no_ray < RAY_FREQ)
	{
		step = 0;
		ray.dof = -1;
		ray.ray_x = g->ply.pos.x;
		ray.ray_y = g->ply.pos.y;
		ray.x_offset = g->setting.check_dist * cos(ray.angle);
		ray.y_offset = g->setting.check_dist * sin(ray.angle);
		// printf("test angle %lf %lf %lf %lf\n", g->setting.check_dist, ray.x_offset, ray.y_offset, ray.angle);
		while (++ ray.dof < g->setting.depth_of_focus)
		{
			step ++;
			ray.ray_x += ray.x_offset;
			ray.ray_y += ray.y_offset;
			// printf("test check loop %d %d %lf %lf\n", (int)ray.ray_x, (int)ray.ray_y, ray.x_offset, ray.y_offset);
			if ((int)ray.ray_x >= 0 && (int)ray.ray_x < g->row && (int)ray.ray_y >= 0 && (int)ray.ray_y < g->size && g->map[(int)ray.ray_x][(int)ray.ray_y] == '1')
			{
				height = MAX_HEIGHT / (g->setting.check_dist * step);
				// printf("test height detect %lf\n", height);
				break ;
			}
		}
		draw_wall(g, ray.no_ray, height);
		new_angle(&ray.angle, ray.angle + g->setting.angle_delta);
	}
}
