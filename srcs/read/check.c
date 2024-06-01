/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:15:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/27 09:14:12 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
check pattern is
check for starting wall '1'
then if there is no whitespace ' \r\n' and not end of line
check for '0' floor 'D' door (bonus) 
and 'NSWE' rep ply and its starting orientation
set_ply_pos store the ply info and change that char to '0'
any other char is invalid char
after the loop check for a closing wall '1'
if no starting or closing wall map border not close
extra whitespace is handle in the parent func
*/
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

/*
1st round of map validation, each row is checked for invalid char and close borders around the
ptr is used to store the longest length which would be the width of the map
*/
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

/*
check and skip every consecutive rows with the same char c
*/
static int	skip_row(const t_map *m, char c, t_int iter)
{
	while (iter.x < m->height && m->map[iter.x * m->width + iter.y] == c)
		iter.x ++;
	return (iter.x);
}

/*
check pattern is
skip whitespace
check for starting wall '1'
then if there is no whitespace ' \r\n' and not end of line
check for '0' floor 'D' door (bonus) 
and 'NSWE' rep ply and its starting orientation
set_ply_pos store the ply info and change that char to '0'
any other char is invalid char
after the loop check for a closing wall '1'
if no starting or closing wall map border not close
*/
static int	check_map_vert_loop(const t_map *m, t_int iter, t_asset *door)
{
	iter.x = skip_row(m, ' ', iter);
	if (iter.x == m->height)
		return (iter.x);
	if (m->map[iter.x * m->width + iter.y] == '1')
		iter.x = skip_row(m, '1', iter);
	else
		return (-1);
	if (iter.x >= m->height || !checkset(m->map[iter.x * m->width + iter.y], "0D"))
		return (iter.x);
	while (iter.x < m->height && checkset(m->map[iter.x * m->width + iter.y], "0D"))
	{
		if (m->map[iter.x * m->width + iter.y] == 'D')
			add_asset(door, iter);
		iter.x ++;
	}
	if (iter.x == m->height && m->map[(iter.x - 1) * m->width + iter.y] != '1')
		return (-1);
	else if (m->map[iter.x * m->width + iter.y] != '1')
		return (-1);
	return (iter.x);
}

/*
2nd round of map validation, each col is checked for invalid char and close borders around the
t_asset is to store door info (ex pos of the door)
*/
int	check_map_vertical(const t_map *m, t_asset *door)
{
	int	row;
	int	col;

	col = -1;
	while (++ col < m->width)
	{
		row = 0;
		while (row < m->height)
		{
			row = check_map_vert_loop(m, (t_int){.x = row, .y = col}, door);
			if (row < 0)
				return (errmsg_config(4), -1);
		}
	}
	return (0);
}
