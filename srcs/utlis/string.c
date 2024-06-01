/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:58 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/25 16:57:56 by lchew            ###   ########.fr       */
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
int skip_till_end(const char *s, const char *ref, int start)
{
	while (s[start] && !checkset(s[start], ref))
		start++;
	return start;
}

/**
 * @brief Checks if a character is in a specific character set.
 * 
 * @param c The character to check.
 * @param s The character set to check against.
 * 
 * @return Returns 1 if the character is in the set, 0 otherwise.
 */
int	checkset(char c, const char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

/**
 * @brief Copies a string from src to dst and stops when it encounters a 
 * '\r' or '\n' character in src.
 * 
 * @param dst The destination string.
 * @param src The source string.
 * 
 * @return The number of characters copied from src to dst.
 * 
 * This function copies characters from the source string (src) to the 
 * destination string (dst) until it encounters a '\r' or '\n' character 
 * in src.
 * It returns the number of characters copied from src to dst.
 */
int	strlcpy_over(char *dst, const char *src)
{
	int	i;

	i = -1;
	while (src[++i])
	{
		dst[i] = src[i];
		if (src[i] == '\r' || src[i] == '\n')
			return (i);
	}
	return (i);
}

/**
 * @brief Checks to the end of the string from a given index, 
 * if a non whitespace is found it will apply
 * the func 'f' to write an errmsg to STDERR
 * 
 * @param line The string to check.
 * @param index The index to start from.
 * @param f The func to print out the errmsg
 * @param errtype the parameter to pass to func f to fetch the right errmsg
 * 
 * @return Returns -1 if non-whitespace character is found, 0 otherwise.
 */
int	check_line_end(const char *line, int index, void (*f)(char ), char errtype)
{
	while (line[index])
	{
		if (!checkset(line[index], " \r\n"))
		{
			if (f)
				f(errtype);
			return (-1);
		}
		index ++;
	}
	return (0);
}
