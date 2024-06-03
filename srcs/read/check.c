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

/**
 * @brief Checks the horizontal validity of a line in the game map.
 *
 * This function checks the horizontal validity of a line in the game map.
 * It starts from the position pointed to by ptr and continues until it
 * encounters a space or the end of the line.
 *
 * If the first character is not '1', it prints an error message and returns 1.
 *
 * For each character, it checks if it is a valid map character. If it is 'N',
 * 'S', 'E', or 'W', it sets the player's position to the current index and
 * replaces the character with '0'. If it is 'D', it increments the door length.
 *
 * If it encounters a character that is not a valid map character and not a
 * newline or carriage return, it prints an error message and returns 1.
 *
 * If the last character before a space or the end of the line is not '1', it
 * prints an error message and returns 1.
 *
 * @param line The line to check.
 * @param ptr A pointer to the position to start checking from.
 * @param g The current game state.
 * @return Returns 0 on success, or 1 if an error occurred.
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

/**
 * @brief Performs the first round of map validation.
 *
 * This function performs the first round of map validation. Each row of the map
 * is checked for invalid characters and for closed borders around the map.
 *
 * The function iterates over each character in the line. If the character is a
 * space, it skips over it. If the character is a carriage return or newline, it
 * breaks out of the loop.
 *
 * It then checks the horizontal validity of the line starting from the current
 * index. If the check fails, it returns 1.
 *
 * If the current index is greater than the value pointed to by ptr, it updates
 * ptr to the current index. ptr is used to store the longest length, which will
 * be the width of the map.
 *
 * @param line The line to check.
 * @param ptr A pointer to the position to start checking from.
 * @param g The current game state.
 * @return Returns 0 on success, or 1 if an error occurred.
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

/**
 * @brief Skips over consecutive rows in the map that contain the same character.
 *
 * This function checks and skips over every consecutive row in the map that 
 * contains the same character. It starts from the row and column specified by 
 * the iter parameter and continues until it encounters a row that does not 
 * contain the character or it reaches the end of the map.
 *
 * @param m The map to check.
 * @param c The character to skip rows for.
 * @param iter A struct containing the starting row and column.
 * @return Returns the index of the first row that does not contain the character.
 */
static int	skip_row(const t_map *m, char c, t_int iter)
{
	while (iter.x < m->height && m->map[iter.x * m->width + iter.y] == c)
		iter.x ++;
	return (iter.x);
}

/**
 * @brief Checks the vertical validity of a map.
 *
 * This function checks the vertical validity of a map. It starts from the 
 * position specified by the iter parameter and continues until it encounters 
 * an invalid character or it reaches the end of the map.
 *
 * The function first skips over any whitespace at the start of the map. It 
 * then checks for a starting wall '1'. If there is no starting wall, it 
 * returns -1.
 *
 * It then checks for '0' (floor), 'D' (door), and 'NSWE' (player and its 
 * starting orientation). If it encounters a character that is not '0', 'D', 
 * or 'NSWE', it returns the current index.
 *
 * If it encounters a 'D', it adds the current position to the door asset.
 *
 * After the loop, it checks for a closing wall '1'. If there is no closing 
 * wall, it returns -1.
 *
 * @param m The map to check.
 * @param iter A struct containing the starting row and column.
 * @param door The door asset to add positions to.
 * @return Returns the index of the first invalid character, or the map height 
 * if the map is valid.
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
	if (iter.x >= m->height
		|| !checkset(m->map[iter.x * m->width + iter.y], "0D"))
		return (iter.x);
	while (iter.x < m->height
		&& checkset(m->map[iter.x * m->width + iter.y], "0D"))
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

/**
 * @brief Performs the second round of map validation.
 *
 * This function performs the second round of map validation. Each column of the
 * map is checked for invalid characters and for closed borders around the map.
 * The door asset is used to store door information, such as the position of the 
 * door.
 *
 * The function iterates over each column in the map. For each column, it checks
 * the vertical validity of the map starting from the top of the column. If the
 * check fails, it prints an error message and returns -1.
 *
 * @param m The map to check.
 * @param door The door asset to store door information in.
 * @return Returns 0 on success, or -1 if an error occurred.
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
