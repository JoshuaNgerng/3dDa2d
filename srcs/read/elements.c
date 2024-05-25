/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:25:35 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/25 15:26:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*skip_empty_line(int fd, char *prev)
{
	char	*ptr;

	ptr = prev;
	while (ptr)
	{
		if (ptr && ptr[0] && !checkset(ptr[0], "\r\n"))
			break ;
		free(ptr);
		if (get_next_line(fd, &ptr))
			return (errmsg_file_errno(1, NULL), NULL);
	}
	return (ptr);
}

static int	get_colour_config(const char *line, uint8_t *ptr, int *index)
{
	int	i;
	int	val;
	int	len;

	i = *index;
	val = 0;
	len = 0;
	if (!line[i])
		return (1);
	while (ft_isdigit(line[i]) && len < 4)
	{
		val = val * 10 + line[i ++] - '0';
		len ++;
	}
	if (val > 255 || val < 0)
		return (1);
	*ptr = (uint8_t)val;
	*index = i;
	return (0);
}

static int	store_element(char *line, int index, t_game *g, int type)
{
	int		iter;
	uint8_t	*ptr;

	index = skip_char(line, ' ', index);
	if (type < 3)
	{
		iter = skip_till_end(line, "\r\n ", index);
		line[iter] = '\0';
		if (load_texture(&g->wall[type],
				g->mlx.mlx, &line[index], iter - index))
			return (-1);
		return (check_line_end(line, index, &errmsg_config, 5));
	}
	iter = 3;
	g->env[type % 4].set = 1;
	ptr = g->env[type % 4].colour.trabg_parts;
	while (iter -- > 0)
	{
		if (get_colour_config(line, ptr + iter, &index))
			return (errmsg_config(3), -1);
		if (line[index ++] != ',' && iter > 0)
			return (errmsg_config_var(1, &line[index], 1), -1);
	}
	return (check_line_end(line, index, &errmsg_config, 5));
}

static int	check_elements(char *line, t_game *g)
{
	int		i;
	int		len;
	int		index;
	char	**dict;

	if (!line[0] || checkset(line[0], "\r\n"))
		return (1);
	index = skip_char(line, ' ', 0);
	i = -1;
	len = 3;
	dict = (char *[6]){"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	while (++ i < 6)
	{
		if (i == 4)
			len = 2;
		if (!ft_strncmp(&line[index], dict[i], len))
			return (store_element(line, index + len, g, i));
	}
	return (1);
}

/**
 * @brief Reads game elements from a file descriptor and stores them into t_game struct.
 * 
 * @param fd The file descriptor from which to read.
 * @param g The t_game structure in which to store the game elements.
 * @param ptr A pointer to a string where the first line of the map will be stored.
 * 
 * @return Returns 0 if a map is detected in the file, and 1 otherwise. If an error occurs in check_elements, the function also returns 1.
 * 
 * The function reads lines from the file descriptor until it reaches the end of the file. For each line, it calls check_elements to check for game elements.
 * If check_elements detects a map (returns a value greater than 0), the function stores the line in ptr and returns 0.
 * If check_elements returns a value less than 0, indicating an error, the function returns 1.
 * If no map is detected in any line, the function returns 1.
 */
int	read_elements(int fd, t_game *g, char **ptr)
{
	int		check;
	char	*buffer;

	if (get_next_line(fd, &buffer))
		return (errmsg_file_errno(1, NULL), 1);
	buffer = skip_empty_line(fd, buffer);
	while (buffer)
	{
		check = check_elements(buffer, g);
		if (check < 0)
			return (free(buffer), 1);
		if (check > 0)
			break ;
		free(buffer);
		if (get_next_line(fd, &buffer))
			return (errmsg_file_errno(1, NULL), 1);
	}
	buffer = skip_empty_line(fd, buffer);
	if (!buffer)
		return (errmsg_config(2), 1);
	*ptr = buffer;
	return (0);
}
