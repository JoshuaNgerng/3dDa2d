/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:10:12 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 15:58:24 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	n;

	if (dst == NULL && dstsize == 0)
		return (0);
	i = 0;
	n = ft_strlen(src);
	j = ft_strlen(dst);
	if (dstsize > 0 && j < dstsize - 1)
	{
		while (i + j < dstsize - 1 && src[i])
		{
			dst[j + i] = src[i];
			i ++;
		}
		dst[j + i] = '\0';
	}
	if (j > dstsize)
		j = dstsize;
	return (n + j);
}
