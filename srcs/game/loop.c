/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:30 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/12 12:54:34 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Sets the player movement options based on the mouse input.
 *
 * This function is called when a mouse button is pressed. It determines the
 * direction of rotation for the player based on the mouse position relative to
 * the center of the window. If the mouse position is to the left of the center,
 * the player will rotate left. If the mouse position is to the right of the
 * center, the player will rotate right. The player movement options are updated
 * accordingly.
 *
 * @param key The mouse button that was pressed.
 * @param pos_x The x-coordinate of the mouse position.
 * @param pos_y The y-coordinate of the mouse position.
 * @param g A pointer to the game structure.
 * @return 0
 */
int	mouse_set_ply(int key, int pos_x, int pos_y, t_game *g)
{
	int	half_width;

	(void) pos_y;
	if (key != 1)
		return (0);
	half_width = g->setting.win_width / 2;
	if (pos_x == half_width)
		return (0);
	if (pos_x < half_width)
		g->ply.move_options |= rotate_left;
	else
		g->ply.move_options |= rotate_right;
	return (0);
}

/**
 * @brief Unsets the player movement options based on the mouse input.
 *
 * This function is called when a mouse button is released. It unsets the
 * rotation options for the player based on the mouse position. If the mouse
 * button released is the left button, it unsets the rotate_left option. If the
 * mouse button released is the right button, it unsets the rotate_right option.
 * The player movement options are updated accordingly.
 *
 * @param key The mouse button that was released.
 * @param pos_x The x-coordinate of the mouse position.
 * @param pos_y The y-coordinate of the mouse position.
 * @param g A pointer to the game structure.
 * @return 0
 */
int	mouse_unset_ply(int key, int pos_x, int pos_y, t_game *g)
{
	(void) pos_x;
	(void) pos_y;
	if (key != 1)
		return (0);
	g->ply.move_options &= ~(rotate_left + rotate_right);
	return (0);
}

/**
 * @brief Sets the player movement options based on the key pressed.
 *
 * This function is responsible for setting the movement options of the player
 * based on the key pressed.
 *
 * @note - escape key - it calls the `free_exit` function to exit the game.
 * @note - up arrow key - it sets the zoom in on the player view
 * @note - down arrow key - it sets the zoom out on the player view
 * @note - 'W' key - it sets the forward movement option.
 * @note - 'S' key - it sets the backward movement option.
 * @note - 'A' key - it sets the left movement option.
 * @note - 'D' key - it sets the right movement option.
 * @note - left arrow key / 'Q' key - it sets the left rotation option.
 * @note - right arrow key / 'E' key - it sets the right rotation option.
 * @note - left shift key / right shift key - it sets the interact door option.
 * @note - 'M' key - it toggles the map option.
 *
 * @param key The key code of the key pressed.
 * @param g A pointer to the game structure.
 * @return Always returns 0.
 */
int	set_ply_mov(int key, t_game *g)
{
	if (key == esc)
		free_exit(g, 0);
	if (key == up)
		g->ply.move_options |= zoom_in;
	else if (key == down)
		g->ply.move_options |= zoom_out;
	else if (key == wkey)
		g->ply.move_options |= forward;
	else if (key == skey)
		g->ply.move_options |= backward;
	else if (key == akey)
		g->ply.move_options |= move_left;
	else if (key == dkey)
		g->ply.move_options |= move_right;
	else if (key == left || key == qkey)
		g->ply.move_options |= rotate_left;
	else if (key == right || key == ekey)
		g->ply.move_options |= rotate_right;
	else if (key == lshift || key == rshift)
		g->ply.move_options |= interact_door;
	else if (key == mkey)
		g->ply.move_options ^= map_option;
	return (0);
}

/**
 * @brief Unsets the player movement options based on the key pressed.
 *
 * This function is responsible for unsetting the player movement options
 * based on the key pressed. It takes the key and a pointer to the game
 * structure as parameters. The function checks the key value and updates
 * the move_options field of the player structure accordingly.
 *
 * @param key The key code of the key pressed.
 * @param g A pointer to the game structure.
 * @return 0
 */
int	unset_ply_mov(int key, t_game *g)
{
	if (key == up)
		g->ply.move_options &= ~zoom_in;
	else if (key == down)
		g->ply.move_options &= ~zoom_out;
	else if (key == wkey)
		g->ply.move_options &= ~forward;
	else if (key == skey)
		g->ply.move_options &= ~backward;
	else if (key == akey)
		g->ply.move_options &= ~move_left;
	else if (key == dkey)
		g->ply.move_options &= ~move_right;
	else if (key == left || key == qkey)
		g->ply.move_options &= ~rotate_left;
	else if (key == right || key == ekey)
		g->ply.move_options &= ~rotate_right;
	return (0);
}

/**
 * @brief The main game loop.
 *
 * This function is responsible for running the main game loop. It updates the
 * player movement, performs raycasting to create a 3D image in the memory,
 * writes the image to the window, creates a minimap image in the memory,
 * writes the minimap to the window, unsets the interact_door options, updates
 * the door information, and returns 0.
 *
 * @param g A pointer to the game structure.
 * @return Always returns 0.
 */
int	main_loop(t_game *g)
{
	update_ply_move(&g->ply, g);
	if (g->ply.move_options & interact_door)
		update_door(&g->map, &g->ply, &g->door);
	raycasting_walls(&g->scene, g);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->scene.img, 0, 0);
	if (g->ply.move_options & map_option)
		create_minimap(&g->minimap, &g->mlx, g);
	g->ply.move_options &= ~interact_door;
	update_door_counter(&g->door);
	return (0);
}
