/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:56 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/11 17:15:45 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	err_handle(int fd)
{
	close(fd);
	return (1);
}

void	free_buffer(t_buffer *b)
{
	t_list_	*ptr;

	if (!b->list)
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
		// printf("%s\n", &out[index]);
		index += width;
		ptr = ptr->next;
	}
	out[index] = '\0';
	return (out);
}

static int	check_ply(t_ply *p)
{
	if (p->pos.x < 0 && p->pos.y < 0)
		return (errmsg_config(0), 1);
	p->pos.x += 0.5;
	p->pos.y += 0.5;
	return (0);
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
		return (err_handle(fd));
	if (init_buffer_list(&buffer, ptr, &g->ply, &g->map.width)
		|| cont_buffer_list(&buffer, fd, &g->map.width, &g->ply))
		return (free_buffer(&buffer), err_handle(fd));
	close(fd);
	g->map.height = buffer.len;
	g->map.map = make_map(&buffer, g->map.width);
	free_buffer(&buffer);
	if (!g->map.map)
		return (errmsg_prog_errno("Cannot make map "
				"from buffer (malloc): ", 38), 1);
	if (check_map_vertical(&g->map))
	{
		printf("Error: Map is not closed\n");
		return (1);
	return (check_ply(&g->ply));
}
