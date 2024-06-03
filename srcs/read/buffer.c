/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:50:17 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 09:14:11 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Creates a new list node in the buffer for a line of text.
 *
 * This function creates a new list node in the buffer for a line of text.
 * It allocates memory for a new list node and checks if the allocation was
 * successful. If not, it prints an error message, frees the line, and
 * returns 1.
 *
 * It then sets the new list node's line to the input line and its next
 * pointer to NULL, and sets the buffer's tail to the new list node. It
 * also increments the buffer's length by 1.
 *
 * @param buffer The buffer to add the new list node to.
 * @param line The line of text to add to the buffer.
 * @return Returns 0 on success, or 1 if an error occurred.
 */
int	init_buffer_list(t_buffer *buffer, char *line, t_game *g)
{
	buffer->list = NULL;
	if (check_map(line, &g->map.width, g))
		return (free(line), 1);
	buffer->list = (t_list_ *) malloc(sizeof(t_list_));
	if (!buffer->list)
		return (free(line), errmsg_prog_errno("Cannot make "
				"buffer for line from read (malloc): ", 48), 1);
	buffer->list->line = line;
	buffer->list->next = NULL;
	buffer->tail = buffer->list;
	buffer->len = 1;
	if (g->ply.pos.y >= 0)
		g->ply.pos.x = 0;
	return (0);
}

/**
 * @brief Creates a new list node in the buffer for a line of text.
 *
 * This function creates a new list node in the buffer for a line of text. It 
 * allocates memory for a new list node and checks if the allocation was 
 * successful. If not, it prints an error message, frees the line, and returns 1.
 *
 * It then sets the new list node's line to the input line and its next pointer 
 * to NULL, and sets the buffer's tail to the new list node. It also increments 
 * the buffer's length by 1.
 *
 * @param buffer The buffer to add the new list node to.
 * @param line The line of text to add to the buffer.
 * @return Returns 0 on success, or 1 if an error occurred.
 */
static int	make_new_list(t_buffer *buffer, char *line)
{
	t_list_	*new;

	new = (t_list_ *) malloc(sizeof(t_list_));
	buffer->tail->next = new;
	if (!new)
	{
		errmsg_prog_errno("Cannot make buffer "
			"for line from read (malloc): ", 48);
		return (free(line), 1);
	}
	new->line = line;
	buffer->tail = new;
	new->next = NULL;
	buffer->len ++;
	return (0);
}

/**
 * @brief Continues to add lines of text from a file to a buffer list.
 *
 * This function continues to add lines of text from a file to a buffer list.
 * It reads lines from the file one by one using the get_next_line function.
 * If reading a line fails, it prints an error message and returns 1.
 *
 * For each line, it checks if the line is a valid map line. If not, it frees
 * the line and returns 1.
 *
 * If the player's x position is not set and the player's y position is set,
 * it sets the player's x position to the current row number.
 *
 * It then creates a new list node in the buffer for the line. If creating the
 * list node fails, it prints an error message and returns 1.
 *
 * @param buffer The buffer to add lines to.
 * @param fd The file descriptor of the file to read lines from.
 * @param g The current game state.
 * @return Returns 0 on success, or 1 if an error occurred.
 */
int	cont_buffer_list(t_buffer *buffer, int fd, t_game *g)
{
	int		row;
	char	*line;

	row = 0;
	if (get_next_line(fd, &line))
		return (errmsg_file_errno(1, NULL), 1);
	while (line && ++ row)
	{
		if (!line[0] || line[0] == '\r' || line[0] == '\n')
			break ;
		if (check_map(line, &g->map.width, g))
			return (free(line), 1);
		if (g->ply.pos.x < 0 && g->ply.pos.y >= 0)
			g->ply.pos.x = (double)row;
		if (make_new_list(buffer, line))
			return (errmsg_prog_errno("Cannot make buffer "
					"for line from read (malloc): ", 48), 1);
		if (get_next_line(fd, &line))
			return (errmsg_file_errno(1, NULL), 1);
	}
	if (line)
		free(line);
	return (0);
}
