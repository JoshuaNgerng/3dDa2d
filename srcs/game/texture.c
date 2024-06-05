/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:12 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 18:31:44 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Loads a texture from an XPM file into an image in memory.
 *
 * This function loads a texture from an XPM file into an image in memory. It 
 * uses the MiniLibX library to convert the XPM file to an image and get the 
 * image's data address. If either operation fails, it prints an error message 
 * and returns 1.
 *
 * @param art The image to load the texture into.
 * @param mlx A pointer to the MiniLibX instance.
 * @param path The path to the XPM file.
 * @param str_len The length of the path string (for error reporting).
 * @return Returns 0 on success, or 1 if an error occurred.
 */
int	load_texture(t_img *art, void *mlx, char *path, size_t str_len)
{
	art->img = mlx_xpm_file_to_image(mlx, path, &art->width, &art->height);
	if (!art->img)
		return (errmsg_img(path, str_len), 1);
	art->pixel_ptr = mlx_get_data_addr(art->img, &art->bits_per_pixel,
			&art->line_length, &art->endian);
	if (!art->pixel_ptr)
		return (errmsg_img(path, str_len), 1);
	return (0);
}

/**
 * @brief Loads a texture from an XPM file into an image in memory.
 *
 * This function loads a texture from an XPM file into an image in memory. It 
 * uses the MiniLibX library to convert the XPM file to an image and get the 
 * image's data address. If either operation fails, it prints an error message 
 * and returns 1.
 *
 * @param art The image to load the texture into.
 * @param mlx A pointer to the MiniLibX instance.
 * @param path The path to the XPM file.
 * @param str_len The length of the path string (for error reporting).
 * @return Returns 0 on success, or 1 if an error occurred.
 */
static int	load_img(t_img *i, void *mlx, int width, int height)
{
	i->width = width;
	i->height = height;
	i->img = mlx_new_image(mlx, width, height);
	if (!i->img)
		return (1);
	i->pixel_ptr = mlx_get_data_addr(i->img,
			&i->bits_per_pixel, &i->line_length, &i->endian);
	if (!i->pixel_ptr)
		return (1);
	return (0);
}

/**
 * @brief Loads wall and door textures into the game state.
 *
 * This function loads wall and door textures into the game state
 * from specified XPM files. 
 * It iterates over an array of file paths, loading each one into
 * a corresponding slot in the game state's wall texture array.
 *
 * If a texture is already loaded at a given index, it skips that index.
 * If loading and a texture fails, it returns 1.
 *
 * If there are doors in the game, it also loads two door textures and 
 * sets the maximum door index based on the height of the first door texture.
 *
 * @param g The game state to load textures into.
 * @return Returns 0 on success, or 1 if an error occurred.
 */
static int	load_texture_wall(t_game *g)
{
	int		i;
	char	**path;
	char	*door;

	i = -1;
	path = (char *[]){"art/wall_2.xpm",
		"art/wall_1.xpm", "art/wall_4.xpm", "art/bluestone.xpm"};
	while (++ i < 4)
	{
		if (g->wall[i].img)
			continue ;
		if (load_texture(&g->wall[i], g->mlx.mlx, path[i], ft_strlen(path[i])))
			return (1);
	}
	if (g->door.len > 0)
	{
		door = "art/eagle.xpm";
		if (load_texture(&g->door_img[0], g->mlx.mlx, door, ft_strlen(door)))
			return (1);
		door = "art/purplestone.xpm";
		if (load_texture(&g->door_img[1], g->mlx.mlx, door, ft_strlen(door)))
			return (1);
		g->door.max_index = g->door_img->height - 10;
	}
	return (0);
}

/**
 * @brief Sets the minimap information for the game.
 *
 * This function sets the minimap information for the game. It sets the block 
 * size, border size, and block border size for the minimap. It also calculates 
 * the number of blocks per row and column based on the minimap dimensions and 
 * block size.
 *
 * Additionally, it sets the colors for different elements of the minimap, 
 * including the grey color for walls, the empty color for empty spaces, the 
 * black color for the player, and the door color for doors.
 *
 * @param m The minimap to set information for.
 * @param g The current game state.
 */
void	set_minimap_info(t_mmap *m, const t_game *g)
{
	m->block_size.y = 15;
	m->block_size.x = 15;
	m->border_size.x = 5;
	m->border_size.y = 5;
	m->block_border_size.x = 2;
	m->block_border_size.y = 2;
	m->block_per_row = (g->setting.minimap_width - m->border_size.x)
		/ m->block_size.x;
	m->block_per_col = (g->setting.minimap_height - m->border_size.y)
		/ m->block_size.y;
	m->grey = (t_colour){.mode.transparency = 150,
		.mode.red = 128, .mode.blue = 128, .mode.green = 128};
	m->empty = (t_colour){.mode.transparency = 175,
		.mode.red = 100, .mode.blue = 50, .mode.green = 50};
	m->black = (t_colour){.mode.transparency = 128};
	m->door = (t_colour){.mode.transparency = 128, .mode.green = 128};
}

/**
 * @brief Loads wall and door textures into the game state.
 *
 * This function loads wall and door textures into the game state from specified 
 * XPM files. It iterates over an array of file paths, loading each one into a 
 * corresponding slot in the game state's wall texture array.
 *
 * If a texture is already loaded at a given index, it skips that index. If 
 * loading a texture fails, it returns 1.
 *
 * If there are doors in the game, it also loads two door textures and sets the 
 * maximum door index based on the height of the first door texture.
 *
 * @param g The game state to load textures into.
 * @return Returns 0 on success, or 1 if an error occurred.
 */
int	load_mlx_img(t_game *g, char *title)
{
	g->mlx.win = mlx_new_window(g->mlx.mlx,
			g->setting.win_width, g->setting.win_height, title);
	if (!g->mlx.win)
		return (errmsg_config_errno(1), 1);
	if (load_texture_wall(g))
		return (1);
	if (!g->env[floor_].set)
		g->env[floor_].colour = (t_colour){.mode.green = 255};
	if (!g->env[sky_].set)
		g->env[sky_].colour = (t_colour){.mode.blue = 255};
	if (load_img(&g->scene, g->mlx.mlx,
			g->setting.win_width, g->setting.win_height))
		return (errmsg_config_errno(2), 1);
	if (load_img(&g->minimap, g->mlx.mlx,
			g->setting.minimap_width, g->setting.minimap_height))
		return (errmsg_config_errno(3), 1);
	set_minimap_info(&g->minimap_info, g);
	return (0);
}
