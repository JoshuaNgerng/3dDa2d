/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:34:52 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 16:16:09 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Performs a raycast check on the game map.
 *
 * This function performs a raycast check on the game map. It determines the 
 * character at the map position being checked and handles it accordingly. If 
 * the character is '0', it handles shadows and doors. If the character is '1', 
 * it handles walls. If the character is 'D', it handles doors.
 *
 * @param r The ray being cast.
 * @param g The game state.
 * @return Returns 0 for shadows and doors, 1 for walls, and -1 for 
 * out of bounds.
 */
static
t_ray_comp	raycast_comp_init(double ply_pos, double ray_perp, double ray_ref)
{
	t_ray_comp	buffer;

	buffer = (t_ray_comp){.map_check = (int)ply_pos,
		.check_dist = modf(ply_pos, &(double){0}), .step_dir = -1,
		.step_size = sqrt(1 + pow(ray_perp / ray_ref, 2.))};
	if (ray_ref >= 0.)
	{
		buffer.step_dir = 1;
		buffer.check_dist = 1.0 - modf(ply_pos, &(double){0});
	}
	buffer.check_dist *= buffer.step_size;
	return (buffer);
}

/**
 * @brief Initializes the raycasting process for a given ray and game state.
 *
 * This function initializes the raycasting process for a given ray and game 
 * state. It calculates the ray's direction based on the player's direction and 
 * view. It then initializes the horizontal and vertical components of the 
 * raycast computation using the player's position and the ray's direction.
 *
 * The function also initializes the ray's final results array with undefined 
 * types and sets the ray's object iterator to 0.
 *
 * @param r The ray to initialize.
 * @param g The current game state.
 */
static void	raycast_init(t_ray *r, const t_game *g)
{
	int		i;
	double	x_pos;

	x_pos = ((2. * (double)(r->ray_no) / (double)g->setting.win_width) - 1.);
	r->ray_dir.x = g->ply.n_dir.x + g->ply.view.x * x_pos;
	r->ray_dir.y = g->ply.n_dir.y + g->ply.view.y * x_pos;
	r->hori = raycast_comp_init(g->ply.pos.x, r->ray_dir.y, r->ray_dir.x);
	r->verti = raycast_comp_init(g->ply.pos.y, r->ray_dir.x, r->ray_dir.y);
	i = -1;
	while (++ i < MAX_RENDER)
		r->fin[i] = (t_ray_fin){.type = undef};
	r->obj_iter = 0;
}

/**
 * @brief Performs the main raycasting loop for a given ray and game state.
 *
 * This function performs the main raycasting loop for a given ray and game 
 * state. It first initializes the raycasting process. Then, as long as the 
 * horizontal or vertical check distance is less than the player's depth of 
 * focus, it continues to perform raycast checks.
 *
 * If the horizontal check distance is less than the vertical check distance, it 
 * updates the horizontal map check and check distance, and sets the ray's side 
 * to horizontal. Otherwise, it updates the vertical map check and check 
 * distance, and sets the ray's side to vertical.
 *
 * After each update, it performs a raycast check. If the check returns a 
 * negative value, it breaks the loop. If the check returns a positive value, it 
 * ends the function and returns 0.
 *
 * If the loop completes without finding a hit, the function returns 1.
 *
 * @param r The ray to cast.
 * @param g The current game state.
 * @return Returns 0 if a hit was found, or 1 if no hit was found.
 */
static int	raycast_loop(t_ray *r, const t_game *g)
{
	int	check;

	raycast_init(r, g);
	while (r->hori.check_dist < g->ply.depth_of_focus
		|| r->verti.check_dist < g->ply.depth_of_focus)
	{
		if (r->hori.check_dist < r->verti.check_dist)
		{
			r->hori.map_check += r->hori.step_dir;
			r->hori.check_dist += r->hori.step_size;
			r->side = horizontal;
		}
		else
		{
			r->verti.map_check += r->verti.step_dir;
			r->verti.check_dist += r->verti.step_size;
			r->side = vertical;
		}
		check = raycast_check(r, g);
		if (check < 0)
			break ;
		if (check > 0)
			return (0);
	}
	return (1);
}

/**
 * @brief Performs raycasting for walls and draws them to an image.
 *
 * This function performs raycasting for walls and draws them to an image. It 
 * iterates over each column of the window width, performing a raycast loop for 
 * each one and drawing the result to the image.
 *
 * @param img The image to draw to.
 * @param g The current game state.
 */
void	raycasting_walls(t_img *img, const t_game *g)
{
	t_ray	ray;

	(void)img;
	ray.ray_no = -1;
	while (++ ray.ray_no < g->setting.win_width)
	{
		raycast_loop(&ray, g);
		draw_obj_to_img(img, &ray, g);
	}
}
