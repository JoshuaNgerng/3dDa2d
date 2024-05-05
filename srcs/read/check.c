/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:15:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/05 17:37:49 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_ply_pos(int col, char dir, t_ply *p)
{
		printf("chk ply pos %f %f\n", p->pos.x, p->pos.y);
	
	if (p->pos.y >= 0)
		return (1); //dup play
	p->pos.y = (double)col;
	if (dir == 'N')
	{
		p->n_dir = (t_point){.x = 0., .y = -1.};
		p->view = (t_point){.x = p->fov, .y = 0.};
	}
	else if (dir == 'E')
	{
		p->n_dir = (t_point){.x = 1., .y = 0.};
		p->view = (t_point){.x = 0., .y = p->fov};
	}
	else if (dir == 'S')
	{
		p->n_dir = (t_point){.x = 0., .y = 1.};
		p->view = (t_point){.x = -p->fov, .y = 0.};
	}
	else if (dir == 'W')
	{
		p->n_dir = (t_point){.x = -1., .y = 0.};
		p->view = (t_point){.x = 0., .y = -p->fov};
	}
	p->p_dir = (t_point){.x = p->n_dir.y, .y = -p->n_dir.x};
	return (0);
}

static int	check_horizontal(char *line, int *ptr, t_ply *p)
{
	int	i;

	i = *ptr;
	printf("line starting pos: %d, line: %s\n", i, line);
	if (line[i] != '1')
		return (1); // border not close
	while (line[i] && line[i] != ' ')
	{
		if (checkset(line[i], "NSWE"))
		{
			if (check_ply_pos(i, line[i], p))
				return (1); // more than 1 ply
			line[i] = '0';
		}
		else if (checkset(line[i], "\r\n"))
			break ;
		else if (!checkset(line[i], "10"))
			return (1); // invalid char
		i ++;
	}
	if (i - 1 >= 0 && line[i - 1] != '1')
		return (1); // border not close
	*ptr = i;
	return (0);
}

int	check_map(char *line, int *ptr, t_ply *p)
{
	int	i;

	i = 0;
	printf("check map line |%s\n", line);
	while (line[i] && line[i] != '\r' && line[i] != '\n')
	{
		i = skip_char(line, " ", i);
		if (check_horizontal(line, &i, p)) // any fail check will return 1
			return (1);
		printf("========================\n");
	}
	if (*ptr < i) // check width, if stored width is smaller than current width
		*ptr = i; // update width
	return (0);
}

static int check_map_vert_loop(const t_map *m, int row, int col)
{
	printf("m->map: %c, m->width: %d, m->height: %d, row: %d, col: %d\n", m->map[row * m->width + col], m->width, m->height, row, col);
	// Loop until a non-empty space is found
	while (row < m->height && m->map[row * m->width + col] == ' ')
		row++;

	// Check if the end of the map is reached
	if (row == m->height)
		return (row);
	
	printf("check wall\n");
	// Check if the current position is a wall
	if (m->map[row * m->width + col] == '1')
	{
		// Loop until a non-wall character is found
		while (row < m->height && m->map[row * m->width + col] == '1')
		{
			printf("m->map: %c, m->width: %d, row: %d, col: %d\n", m->map[row * m->width + col], m->width, row, col);
			row++;
		}
	}
	else
		return (-1); // error if not wall

	// Move to the next row
	// row++;
	// Check if the end of the map is reached
	if (row >= m->height)
		return (row);

	printf("-m->map: %c, m->width: %d, row: %d, col: %d\n", m->map[row * m->width + col], m->width, row, col);
	// Check if the current position is not an empty space
	if (m->map[row * m->width + col] != '0')
		return (row);

	// Loop until a non-zero character is found
	while (row < m->height && m->map[row * m->width + col] == '0')
		row++;
	printf("row 1: %d\n", row);
	// Check if the current position is not a wall
	if(row == m->height && m->map[(row - 1) * m->width + col] != '1')
		return (-1);
	else if (m->map[row * m->width + col] != '1')
		return (-1);
	return (row);
}

int check_map_vertical(const t_map *m)
{
	int row;
	int col;

	// Print map information
	printf("m->width: %d, m->height: %d, m->unit_size: %d\n", m->width, m->height, m->unit_size);
	printf("m->map: %s\n", m->map);
	col = -1;
	// Loop through each column of the map
	while (++col < m->width)
	{
		row = 0;
		// Loop through each row of the map
		while (row < m->height)
		{
			// Call the check_map_vert_loop function to check the vertical map
			row = check_map_vert_loop(m, row, col);
			printf("row cmv: %d\n", row);
			// Check if an error occurred in the check_map_vert_loop function
			if (row < 0)
				return (-1);
		}
	}

	return (0);
}
