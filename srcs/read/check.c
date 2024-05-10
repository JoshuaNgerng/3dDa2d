/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:15:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/10 11:22:15 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_ply_pos(int col, char dir, t_ply *p)
{
	if (p->pos.x >= 0)
		return (1);
	p->pos.y = (double)col;
	if (dir == 'N')
	{
		p->n_dir = (t_point){.x = -1., .y = 0.};
		p->view = (t_point){.x = 0., .y = p->fov};
	}
	else if (dir == 'E')
	{
		p->n_dir = (t_point){.x = 0., .y = 1.};
		p->view = (t_point){.x = p->fov, .y = 0.};
	}
	else if (dir == 'S')
	{
		p->n_dir = (t_point){.x = 1., .y = 0.};
		p->view = (t_point){.x = 0., .y = -p->fov};
	}
	else if (dir == 'W')
	{
		p->n_dir = (t_point){.x = 0., .y = -1.};
		p->view = (t_point){.x = -p->fov, .y = 0.};
	}
	p->p_dir = (t_point){.x = -p->n_dir.y, .y = p->n_dir.x};
	return (0);
}

static int	check_horizontal(char *line, int *ptr, t_ply *p)
{
	int	i;

	i = *ptr;
	if (line[i] != '1')
		return (errmsg_config(4), 1);
	while (line[i] && line[i] != ' ')
	{
		if (checkset(line[i], "NSWE"))
		{
			if (check_ply_pos(i, line[i], p))
				return (errmsg_config(1), 1);
			line[i] = '0';
		}
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

int	check_map(char *line, int *ptr, t_ply *p)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = skip_char(line, ' ', i);
		if (!line[i] || line[i] == '\r' || line[i] == '\n')
			break ;
		if (check_horizontal(line, &i, p))
			return (1);
	}
	if (*ptr < i)
		*ptr = i;
	return (0);
}

static int	check_map_vert_loop(const t_map *m, int row, int col)
{
	while (row < m->heigth && m->map[row * m->width + col] == ' ')
		row ++;
	if (row == m->heigth)
		return (row);
	if (m->map[row * m->width + col] == '1')
	{
		while (row < m->heigth && m->map[row * m->width + col] == '1')
			row ++;
	}
	else
		return (-1);
	if (row >= m->heigth)
		return (row);
	if (m->map[row * m->width + col] != '0')
		return (row);
	while (row < m->heigth && m->map[row * m->width + col] == '0')
		row ++;
	if (row >= m->heigth || m->map[row * m->width + col] != '1')
		return (-1);
	return (row);
}

int	check_map_vertical(const t_map *m)
{
	int	row;
	int	col;

	col = -1;
	while (++ col < m->width)
	{
		row = 0;
		while (row < m->heigth)
		{
			row = check_map_vert_loop(m, row, col);
			if (row < 0)
				return (errmsg_config(4), -1);
		}
	}
	return (0);
}
