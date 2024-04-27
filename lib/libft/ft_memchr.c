/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:19:12 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 15:56:12 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (*(unsigned char *)s != (unsigned char)c && n > 0)
	{
		s ++;
		n --;
		if (n == 0)
			break ;
	}
	if (n == 0)
		return (NULL);
	return ((void *)s);
}
