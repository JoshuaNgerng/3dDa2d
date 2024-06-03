/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:56 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 17:53:16 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Frees the buffer linked list and closes any opened file descriptor.
 *
 * This function frees the memory allocated for the buffer linked list and 
 * closes any file descriptor that is open. The file descriptor is considered 
 * open if its value is greater than 2.
 *
 * The function first checks if the file descriptor is open. If it is, it 
 * closes the file descriptor.
 *
 * It then checks if the buffer or the list in the buffer is null. If either 
 * is null, it returns 1.
 *
 * It then enters a loop where it frees the memory allocated for each node in 
 * the list. It first stores the current node in a temporary pointer, then 
 * moves the list pointer to the next node. It then frees the line in the 
 * current node and the node itself.
 *
 * After all nodes have been freed, it returns 1.
 *
 * @param fd The file descriptor to close.
 * @param b The buffer containing the list to free.
 * @return Returns 1.
 */
int	free_buffer_n_fd(int fd, t_buffer *b)
{
	t_list_	*ptr;

	if (fd > 2)
		close(fd);
	if (!b || !b->list)
		return (1);
	while (b->list)
	{
		ptr = b->list;
		b->list = b->list->next;
		if (ptr->line)
			free(ptr->line);
		free(ptr);
	}
	return (1);
}

/**
 * @brief Compresses map information into a single array for efficient memory 
 * usage and faster indexing.
 *
 * This function takes the map information stored in a linked list buffer and 
 * compresses it into a single array. This is done to make the map information 
 * more memory efficient and to speed up indexing when reading from the map.
 *
 * The function first allocates memory for the map array based on the width 
 * and length of the buffer. If memory allocation fails, it returns 1.
 *
 * It then enters a loop where it copies each line from the buffer into the 
 * map array. If the length of the line is less than the width, it pads the 
 * rest of the line with spaces. It then increments the index by the width 
 * and moves on to the next line in the buffer.
 *
 * After all lines have been copied, it adds a null character at the end of 
 * the map array and returns 0.
 *
 * @param m The map to store the compressed information in.
 * @param buffer The buffer containing the map information.
 * @param width The width of the map.
 * @return Returns 0 on success, or 1 if memory allocation failed.
 */
static int	make_map(t_map *m, const t_buffer *buffer, int width)
{
	int		len;
	int		index;
	t_list_	*ptr;

	m->height = buffer->len;
	m->map = (char *) malloc(((width * buffer->len) + 1) * sizeof(char));
	if (!m->map)
		return (1);
	ptr = buffer->list;
	index = 0;
	while (ptr)
	{
		len = strlcpy_over(&m->map[index], ptr->line);
		while (len < width)
			m->map[index + len ++] = ' ';
		m->map[index + width] = '\0';
		index += width;
		ptr = ptr->next;
	}
	m->map[index] = '\0';
	return (0);
}

/**
 * @brief Allocates memory for door information if at least one 'D' is read 
 * from the map.
 *
 * This function checks if the length of the door information in the game state 
 * is greater than 0, indicating that at least one 'D' has been read from the 
 * map. If it is, the function allocates memory for the door sprite array in 
 * the game state.
 *
 * The size of the allocated memory is the length of the door information 
 * multiplied by the size of a t_ani structure. If memory allocation fails, 
 * the function returns 1.
 *
 * @param g The game state containing the door information.
 * @return Returns 0 on success, or 1 if memory allocation failed.
 */
int	load_game_components(t_game *g)
{
	if (g->door.len > 0)
	{
		g->door.sprite = (t_ani *) malloc(g->door.len * sizeof(t_ani));
		if (!g->door.sprite)
			return (1);
	}
	return (0);
}

/**
 * @brief Reads a game configuration file and initializes the game state.
 *
 * This function opens a game configuration file and reads the element and map 
 * information. It then initializes the game state based on the information 
 * read from the file.
 *
 * The function first opens the file for reading. If the file cannot be opened, 
 * it prints an error message and returns 1.
 *
 * It then reads the element information from the file and initializes the 
 * buffer list. If any of these operations fail, it frees any allocated memory 
 * and returns 1.
 *
 * It then creates the map from the buffer and loads the game components. If 
 * any of these operations fail, it frees any allocated memory and returns 1.
 *
 * Finally, it checks the vertical validity of the map and the player's 
 * position. If either of these checks fail, it returns 1.
 *
 * @param g The game state to initialize.
 * @param file The path to the game configuration file.
 * @return Returns 0 on success, or 1 if an error occurred.
 */
int	read_file(t_game *g, const char *file)
{
	int			fd;
	char		*ptr;
	t_buffer	buffer;

	ptr = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (errmsg_file_errno(0, NULL), 1);
	if (read_elements(fd, g, &ptr))
		return (free_buffer_n_fd(fd, NULL));
	if (init_buffer_list(&buffer, ptr, g)
		|| cont_buffer_list(&buffer, fd, g))
		return (free_buffer_n_fd(fd, &buffer));
	if (make_map(&g->map, &buffer, g->map.width))
		return (errmsg_prog_errno("Cannot make map"
				" from buffer (malloc): ", 38), free_buffer_n_fd(fd, &buffer));
	free_buffer_n_fd(fd, &buffer);
	if (load_game_components(g))
		return (1);
	if (check_map_vertical(&g->map, &g->door))
		return (1);
	if (g->ply.pos.x < 0 && g->ply.pos.y < 0)
		return (errmsg_config(0), 1);
	g->ply.pos = (t_point){.x = g->ply.pos.x + 0.5, .y = g->ply.pos.y + 0.5};
	return (0);
}
