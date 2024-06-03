/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:41:17 by lchew             #+#    #+#             */
/*   Updated: 2024/06/03 17:42:30 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Skips over occurrences of a specific character in a string, 
 * starting from a given index.
 * 
 * @param s The string to process.
 * @param c The character to skip.
 * @param i The index at which to start skipping.
 * 
 * @return Returns the index of the first occurrence of a character 'c' 
 * after 'i', or the end of the string if no such character is found.
 */
int	skip_char(const char *s, char c, int i)
{
	while (s[i])
	{
		if (s[i] != c)
			break ;
		++i;
	}
	return (i);
}

/**
 * @brief Skips over any occurrences of a set of characters in a string, 
 * starting from a given index.
 * 
 * @param s The string to process.
 * @param ref The character set to skip.
 * @param start The index at which to start skipping.
 * 
 * @return Returns the index of the first occurrence of a character
 * not in the character set 'ref' after 'start', or the end of the string.
 */
int	skip_till_end(const char *s, const char *ref, int start)
{
	while (s[start] && !checkset(s[start], ref))
		start++;
	return (start);
}

/**
 * @brief Continues reading from a file and skips empty lines.
 *
 * This function continues reading from a file and skips any empty lines. An 
 * empty line is defined as a line that contains only a null character ('\0') 
 * or carriage return and newline characters ("\r\n").
 *
 * The function uses the get_next_line function to read lines from the file. 
 * For each line, it checks if the first character is not a carriage return or 
 * newline. If it is, it frees the line and reads the next line. If it is not, 
 * it breaks out of the loop and returns the line.
 *
 * If reading a line fails, it prints an error message and returns NULL.
 *
 * @param fd The file descriptor of the file to read lines from.
 * @param prev The previous line read from the file.
 * @return Returns the first non-empty line read from the file, or NULL if an 
 * error occurred.
 */
char	*skip_empty_line(int fd, char *prev)
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
