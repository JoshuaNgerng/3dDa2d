/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:56 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 09:22:31 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
free the buffer link list
and close any fd opened
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

/*
make map info into a single array
compress the different line in the link list buffer into a single array
(reason more memory eff and faster indexing (read from map))
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

/*
malloc door info if at least one 'D' is read from map
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

/*
open and read file
extract element info first
then map info
free all buffer and close any fd
possible err
cant open file
invalid map / element info
not enough memory to malloc
cant make mlx image from path given in the file
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
