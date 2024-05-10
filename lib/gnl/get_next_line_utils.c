/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:21 by jngerng           #+#    #+#             */
/*   Updated: 2022/11/03 12:11:59 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_sp_strchr(const char *s, int c, int *i)
{
	if (!s)
		return (NULL);
	while (*s != (unsigned char)c && *s != '\0')
	{
		s ++;
		(*i)++;
	}
	if (*s != (unsigned char)c)
		return (((char *)0));
	(*i)++;
	return ((char *)s);
}

void	set_err(int *err)
{
	*err = 1;
}
