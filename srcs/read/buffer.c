/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:50:17 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/14 10:22:35 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3d.h"

int	init_buffer_list(t_buffer *buffer, char *line, t_ply *p, int *ptr_width)
{
	buffer->list = NULL;
	if (check_map(line, ptr_width, p))
		return (free(line), 1);
	buffer->list = (t_list_ *) malloc(sizeof(t_list_));
	if (!buffer->list)
		return (free(line), errmsg_prog_errno("Cannot make "
				"buffer for line from read (malloc): ", 48), 1);
	buffer->list->line = line;
	buffer->list->next = NULL;
	buffer->tail = buffer->list;
	buffer->len = 1;
	if (p->pos.y >= 0)
		p->pos.x = 0;
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
		return (1);
	}
	new->line = line;
	buffer->tail = new;
	new->next = NULL;
	buffer->len ++;
	return (0);
}

int	cont_buffer_list(t_buffer *buffer, int fd, int *ptr, t_ply *p)
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
		if (check_map(line, ptr, p))
			return (free(line), 1);
		if (p->pos.x < 0 && p->pos.y >= 0)
			p->pos.x = (double)row;
		if (make_new_list(buffer, line))
			return (free(line), errmsg_prog_errno("Cannot make buffer "
			"for line from read (malloc): ", 48), 1);
		if (get_next_line(fd, &line))
			return (errmsg_file_errno(1, NULL), 1);
	}
	buffer->tail->next = NULL;
	if (line)
		free(line);
	return (0);
}
