/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:56 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/17 14:18:21 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_buffer_n_fd(int fd, t_buffer *b)
{
	t_list_	*ptr;

	if (fd > 2)
		close(fd);
	if (!b || !b->list)
		return ;
	while (b->list)
	{
		ptr = b->list;
		b->list = b->list->next;
		if (ptr->line)
			free(ptr->line);
		free(ptr);
	}
}

static char	*make_map(const t_buffer *buffer, int width)
{
	int		len;
	int		index;
	t_list_	*ptr;
	char	*out;

	out = (char *) malloc(((width * buffer->len) + 1) * sizeof(char));
	if (!out)
		return (NULL);
	ptr = buffer->list;
	index = 0;
	while (ptr)
	{
		len = strlcpy_over(&out[index], ptr->line);
		while (len < width)
			out[index + len ++] = ' ';
		out[index + width] = '\0';
		index += width;
		ptr = ptr->next;
	}
	out[index] = '\0';
	return (out);
}

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
		return (free_buffer_n_fd(fd, NULL), 1);
	if (init_buffer_list(&buffer, ptr, &g->ply, &g->map.width))
		return (free_buffer_n_fd(fd, &buffer), 1);
	if (cont_buffer_list(&buffer, fd, &g->map.width, &g->ply))
		return (free_buffer_n_fd(fd, &buffer), 1);
	g->map.height = buffer.len;
	g->map.map = make_map(&buffer, g->map.width);
	free_buffer_n_fd(fd, &buffer);
	if (!g->map.map)
		return (errmsg_prog_errno("Cannot make map "
				"from buffer (malloc): ", 38), 1);
	if (check_map_vertical(&g->map))
		return (1);
	if (g->ply.pos.x < 0 || g->ply.pos.y < 0)
		return (errmsg_config(0), 1);
	g->ply.pos = (t_point){.x = g->ply.pos.x + 0.5, .y = g->ply.pos.y + 0.5};
	return (0);
}
