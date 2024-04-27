/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:25:35 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/18 16:26:20 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	get_colour_config(const char *line, uint8_t *ptr, int *index)
{
	int	i;
	int	val;

	i = *index;
	val = 0;
	if (!line[i])
		return (1); // need three numbers
	if (line[i] == '-')
		return (1); // cannot be negative
	while (ft_isdigit(line[i]))
		val = val * 10 + line[i ++] - '0';
	if (val > 255)
		return (1); // cannot exceed 255
	*ptr = (uint8_t)val;
	return (0);
}

static int	store_element(char *line, int i, t_game *g, int j)
{
	int	iter;

	if (j < 3)
	{
		i = skip_char(line, ' ', i);
		if (load_texture(&g->wall[j], g->mlx.mlx, &line[i], -1))
			return (-1);
		return (0);
	}
	g->env[j % 3].set = 1;
	g->env[j % 3].colour.trabg_parts[3] = NO_TRANSPARENCY;
	iter = 0;
	while (++ iter < 3)
	{
		if (get_colour_config(line, &g->env[j % 3].colour.trabg_parts[3 - iter], &i))
			return (-1);
		if (line[i] != ',')
			return (-1); // delimited by ,
	}
	if (get_colour_config(line, &g->env[j % 3].colour.trabg_parts[3 - iter], &i))
		return (-1);
	return (0);
}

static int	check_elements(char *line, t_game *g)
{
	int		i;
	int		len;
	int		index;
	char	**dict;

	if (!line[0] || checkset(line[0], "\r\n"))
		return (0);
	index = skip_char(line, ' ', 0);
	i = -1;
	len = 3;
	dict = (char *[6]){"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	while (++ i < 6)
	{
		if (i == 4)
			len = 2;
		if (!ft_strncmp(&line[index], dict[i], len))
			return (store_element(line, index, g, i + len));
	}
	if (!check_map(line, &g->map.width, &g->ply))
		return (1);
	return (-1);
}

int	read_elements(int fd, t_game *g, char **ptr)
{
	int		check;
	char	*buffer;

	check = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		check = check_elements(buffer, g);
		if (check > 0)
		{
			*ptr = buffer;
			return (0);
		}
		free(buffer);
		if (check < 0)
			return (1);
		buffer = get_next_line(fd);
	}
	return (1); // map not detected
}
