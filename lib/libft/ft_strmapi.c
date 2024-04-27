/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:59:15 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/18 16:57:24 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				n;
	unsigned int	i;
	char			*out;

	if (!s)
		return (NULL);
	i = 0;
	n = ft_strlen((char *)s);
	out = (char *)ft_calloc(n + 1, sizeof(char));
	if (out == NULL)
		return (out);
	while (s[i])
	{
		out[i] = f(i, *(char *)(s + i));
		i ++;
	}
	return (out);
}
