/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:50:17 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/25 15:57:24 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
