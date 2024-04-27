/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 01:35:27 by jngerng           #+#    #+#             */
/*   Updated: 2022/12/08 17:39:03 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *out, const char *src)
{
	char	*buffer;

	buffer = out;
	while (*buffer)
		buffer ++;
	while (*src)
	{
		*buffer = *src;
		buffer ++;
		src ++;
	}
	*buffer = '\0';
	return (out);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_a;
	int		len_b;
	char	*out;

	if (!s1 || !s2)
		return (NULL);
	len_a = ft_strlen(s1);
	len_b = ft_strlen(s2);
	out = (char *)malloc((len_a + len_b + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	out[0] = '\0';
	if (*s1)
		out = ft_strcat(out, s1);
	if (*s2)
		out = ft_strcat(out, s2);
	return (out);
}
