/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:50:17 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/06 10:01:42 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_buffer_list(t_buffer *buffer, char *line, t_ply *p)
{
	buffer->list = (t_list_ *) malloc(sizeof(t_list_));
	if (!buffer->list)
		return (free(line), 1);
	buffer->list->line = line;
	buffer->list->next = NULL;
	buffer->tail = buffer->list;
	buffer->len = 1;
	if (p->pos.y >= 0)
		p->pos.x = 0;
	return (0);
}

static void	check_free(char *s)
{
	if (s)
		free(s);
}

int	cont_buffer_list(t_buffer *buffer, int fd, int *ptr, t_ply *p)
{
	int		row;
	char	*line;
	t_list_	*new;

	row = 0;
	line = get_next_line(fd);
	while (line && ++ row)
	{
		if (!line[0] || line[0] == '\r' || line[0] == '\n')
			break ;
		if (check_map(line, ptr, p))
			return (free(line), 1);
		if (p->pos.x < 0 && p->pos.y >= 0)
			p->pos.x = (double)row;
		new = (t_list_ *) malloc(sizeof(t_list_));
		buffer->tail->next = new;
		if (!new)
			return (free(line), 1); // error msg malloc
		new->line = line;
		buffer->tail = buffer->tail->next;
		buffer->len ++;
		line = get_next_line(fd);
	}
	buffer->tail->next = NULL;
	return (check_free(line), 0);
}
