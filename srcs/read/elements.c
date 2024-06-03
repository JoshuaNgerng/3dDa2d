/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:25:35 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 17:50:37 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Extracts and stores the RGB value of the floor or sky from a line.
 *
 * This function reads from a line and stores the RGB value of the floor or 
 * sky. It starts from the position specified by the index parameter and 
 * continues until it has read an RGB component value or it encounters an 
 * invalid character.
 *
 * The function first checks if the current character is a digit. If it is, 
 * it multiplies the current value by 10 and adds the digit to the value. 
 * It then increments the index and the length.
 *
 * If the value is greater than 255 or less than 0, it returns 1 to indicate 
 * an invalid RGB format. Otherwise, it stores the value in the location 
 * pointed to by the ptr parameter and updates the index parameter to the 
 * current index.
 *
 * @param line The line to extract the RGB value from.
 * @param ptr A pointer to the location to store the RGB component value.
 * @param index A pointer to the index to start reading from.
 * @return Returns 0 on success, or 1 if an invalid RGB format was encountered.
 */
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

/**
 * @brief Checks and loads a texture for a game element.
 *
 * This function checks and loads a texture for a game element from a line 
 * read from a file. The texture is specified by a path in the line, starting 
 * from the position specified by the index parameter.
 *
 * The function first skips over any whitespace or newline characters at the 
 * start of the line. If there are any characters after the path, it checks 
 * if they are valid. If they are not, it prints an error message and returns 
 * -1.
 *
 * It then loads the texture from the path and stores it in the wall array 
 * of the game state. If loading the texture fails, it returns -1.
 *
 * @param line The line to read the texture path from.
 * @param index The index to start reading from.
 * @param g The game state to store the texture in.
 * @param type The type of the game element.
 * @return Returns 0 on success, or -1 if an error occurred.
 */
static int	check_texture(char *line, int index, t_game *g, int type)
{
	int	iter;

	iter = skip_till_end(line, "\r\n ", index);
	if (line[iter])
	{
		if (check_line_end(line, iter, &errmsg_config, 5))
			return (-1);
	}
	line[iter] = '\0';
	if (load_texture(&g->wall[type],
			g->mlx.mlx, &line[index], iter - index))
		return (-1);
	return (0);
}

/**
 * @brief Stores the element identifier from a file.
 *
 * This function stores the element identifier from a file. The element 
 * identifier can be either the texture of a wall or the RGB value of the 
 * floor or sky.
 *
 * If the type is less than 4, the function treats the identifier as a 
 * texture. It skips over any whitespace at the start of the line, then 
 * reads the texture path until it encounters a whitespace or the end of 
 * the line. It then loads the texture and stores it in the wall array.
 *
 * If the type is 4 or greater, the function treats the identifier as an 
 * RGB value. It sets the corresponding environment variable to 1 and 
 * extracts the RGB components from the line. If any component is invalid, 
 * it prints an error message and returns -1.
 *
 * @param line The line to read the identifier from.
 * @param index The index to start reading from.
 * @param g The game state to store the identifier in.
 * @param type The type of the identifier.
 * @return Returns 0 on success, or -1 if an error occurred.
 */
static int	store_element(char *line, int index, t_game *g, int type)
{
	int		iter;
	uint8_t	*ptr;

	index = skip_char(line, ' ', index);
	if (type < 4)
		return (check_texture(line, index, g, type));
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

/**
 * @brief Checks for valid element identifier and stores the info into the 
 * main game struct.
 *
 * This function checks a line for a valid element identifier and stores the 
 * corresponding information into the main game struct. The element identifier 
 * can be one of the following: "NO ", "SO ", "WE ", "EA ", "F ", "C ".
 *
 * The function first checks if the line is empty or contains only a carriage 
 * return or newline. If it does, the function returns 1 or 0 respectively.
 *
 * It then skips over any leading spaces in the line and checks the remaining 
 * part of the line against each element identifier in the dictionary. If it 
 * finds a match, it calls the store_element function to store the element 
 * information in the game struct and returns the result.
 *
 * If no match is found, the function returns 1.
 *
 * @param line The line to check for an element identifier.
 * @param g The game struct to store the element information in.
 * @return Returns 0 on success, or 1 if an error occurred or no match was found.
 */
static int	check_elements(char *line, t_game *g)
{
	int		i;
	int		len;
	int		index;
	char	**dict;

	if (!line[0])
		return (1);
	if (checkset(line[0], "\r\n"))
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
			return (store_element(line, index + len, g, i));
	}
	return (1);
}

/**
 * @brief Reads game elements from a file and stores them in the game state.
 *
 * This function reads game elements from a file and stores them in the game 
 * state. The elements are read line by line, and each line is checked for 
 * valid elements.
 *
 * The function first reads a line from the file. If reading fails, it prints 
 * an error message and returns 1.
 *
 * It then skips any empty lines and enters a loop where it checks each line 
 * for valid elements. If an error occurs during checking, it frees the line 
 * and returns 1. If no elements are found, it breaks out of the loop.
 *
 * After the loop, it skips any empty lines again. If there are no more lines, 
 * it prints an error message and returns 1.
 *
 * Finally, it stores the last read line in the location pointed to by the 
 * ptr parameter and returns 0.
 *
 * @param fd The file descriptor of the file to read from.
 * @param g The game state to store the elements in.
 * @param ptr A pointer to the location to store the last read line.
 * @return Returns 0 on success, or 1 if an error occurred.
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
