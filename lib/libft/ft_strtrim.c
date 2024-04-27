/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:56:53 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 10:53:32 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char const s1, char const *set)
{
	while (*set)
	{
		if (*set == s1)
			return (1);
		set ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s;
	int		n;
	char	*out;

	if (!s1 || !set)
		return (NULL);
	s = -1;
	while (s1[++ s] && ft_checkset(s1[s], set))
		;
	n = ft_strlen(s1) + 1;
	while (-- n > s && ft_checkset(s1[n - 1], set))
		;
	out = (char *) malloc ((n - s + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (s < n)
		out[i++] = s1[s++];
	out[i] = '\0';
	return (out);
}
