/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:30:27 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 10:54:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i ++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i ++;
	}
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		l_str;
	char	*out;

	if (!s)
		return (NULL);
	l_str = ft_strlen(s);
	if ((int)len > l_str)
		len = (size_t)l_str;
	out = (char *) ft_calloc (len + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	if ((int)start >= l_str)
		return (out);
	out = ft_strncpy(out, &s[start], len);
	return (out);
}
