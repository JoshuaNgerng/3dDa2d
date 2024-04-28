/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:40:18 by jngerng           #+#    #+#             */
/*   Updated: 2024/04/28 15:37:18 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Skips over occurrences of a specific character set in a string, 
 * starting from a given index.
 * 
 * @param s The string to process.
 * @param c The character set to skip.
 * @param i The index at which to start skipping.
 * 
 * @return Returns the index of the first occurrence of a character not in 'set' 
 * after 'i', or the end of the string if no such character is found.
 */
int skip_char(const char *s, char *set, int i)
{
	while (s[i])
	{
		if (!checkset(s[i], set))
			break ;
		++i;
	}
	return (i);
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

int	strlcpy_over(char *dst, const char *src)
{
	int	i;

	i = -1;
	while (src[++ i])
	{
		dst[i] = src[i];
		if (src[i] == '\r' || src[i] == '\n')
			return (i);
	}
	return (i);
}
