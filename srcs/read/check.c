/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:15:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/25 16:42:50 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_horizontal(char *line, int *ptr, t_game *g)
{
	int	i;

	i = *ptr;
	if (line[i] != '1')
		return (errmsg_config(4), 1);
	while (line[i] && line[i] != ' ')
	{
		if (checkset(line[i], "NSWE"))
		{
			if (set_ply_pos(i, line[i], &g->ply))
				return (errmsg_config(1), 1);
			line[i] = '0';
		}
		else if (line[i] == 'D')
			g->door.len ++;
		else if (line[i] == 'K')
			g->key.len ++;
		else if (checkset(line[i], "\r\n"))
			break ;
		else if (!checkset(line[i], "10"))
			return (errmsg_config_var(0, &line[i], 1), 1);
		i ++;
	}
	if (i - 1 >= 0 && line[i - 1] != '1')
		return (errmsg_config(4), 1);
	*ptr = i;
	return (0);
}

int	check_map(char *line, int *ptr, t_game *g)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = skip_char(line, ' ', i);
		if (line[i] == '\r' || line[i] == '\n')
			break ;
		if (check_horizontal(line, &i, g))
			return (1);
	}
	if (*ptr < i)
		*ptr = i;
	return (0);
}

static int	skip_row(const t_map *m, char c, t_int iter)
{
	while (iter.x < m->height && m->map[iter.x * m->width + iter.y] == c)
		iter.x ++;
	return (iter.x);
}

static int	check_map_vert_loop(const t_map *m, t_int iter, t_asset *door, t_asset *key)
{
	iter.x = skip_row(m, ' ', iter);
	if (iter.x == m->height)
		return (iter.x);
	if (m->map[iter.x * m->width + iter.y] == '1')
		iter.x = skip_row(m, '1', iter);
	else
		return (-1);
	if (iter.x >= m->height || !checkset(m->map[iter.x * m->width + iter.y], "0DK"))
		return (iter.x);
	while (checkset(m->map[iter.x * m->width + iter.y], "0DK"))
	{
		if (m->map[iter.x * m->width + iter.y] == 'D')
			add_asset(door, iter, 0);
		if (m->map[iter.x * m->width + iter.y] == 'K')
			add_asset(key, iter, key->max_index % 4);
		iter.x ++;
	}
	if (iter.x == m->height && m->map[(iter.x - 1) * m->width + iter.y] != '1')
		return (-1);
	else if (m->map[iter.x * m->width + iter.y] != '1')
		return (-1);
	return (iter.x);
}

int	check_map_vertical(const t_map *m, t_asset *door, t_asset *key)
{
	int	row;
	int	col;

	col = -1;
	while (++ col < m->width)
	{
		row = 0;
		while (row < m->height)
		{
			row = check_map_vert_loop(m, (t_int){.x = row, .y = col}, door, key);
			if (row < 0)
				return (errmsg_config(4), -1);
		}
	}
	return (0);
}
