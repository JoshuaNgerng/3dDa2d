/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:40:18 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/08 14:13:00 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	skip_char(const char *s, char c, int start)
{
	while (s[start] && s[start] == c)
		start ++;
	return (start);
}

int	skip_till_end(const char *s, const char *ref, int start)
{
	while (s[start] && !checkset(s[start], ref))
		start ++;
	return (start);
}

int	checkset(char c, const char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s ++;
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
