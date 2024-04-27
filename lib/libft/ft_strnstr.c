/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 01:15:50 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/19 17:23:02 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	int		len;
	size_t	i;

	i = 0;
	len = ft_strlen((char *)needle);
	if (haystack == NULL && n == 0)
		return (NULL);
	if (len == 0)
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		if (haystack[i] == needle[0] && i + len - 1 < n)
			if (ft_strncmp((char *)(haystack + i), (char *)needle, len) == 0)
				return ((char *)(haystack + i));
		i ++;
	}
	return (NULL);
}
