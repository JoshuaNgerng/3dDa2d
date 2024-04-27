/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 01:50:15 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/19 11:10:30 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen((char *)src);
	if (dstsize == 0)
		return (n);
	else
	{
		while (i < dstsize - 1 && i < n)
		{
			dst[i] = src[i];
			i ++;
		}
	}
	dst[i] = '\0';
	return (n);
}
