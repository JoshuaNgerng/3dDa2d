/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 04:05:54 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 10:50:43 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	get_str(char *dest, char const *src, char sep, int *index)
{
	int	i;
	int	j;

	i = *index;
	j = 0;
	while (src[i] == sep && src[i])
		i ++;
	while (src[i])
	{
		if (src[i] != sep)
		{
			dest[j] = src[i];
			j ++;
		}
		if (src[i] == sep)
		{
			*index = i;
			dest[j] = '\0';
			return ;
		}
		i ++;
	}
	dest[j] = '\0';
}

static int	get_size(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (s[0] == '\0')
		return (0);
	if (s[0] == c)
		j = 0;
	while (s[++ i])
		if (s[i] != c && s[i - 1] == c)
			j += 1;
	return (j);
}

static int	get_len_str(char const *s, char c, int index)
{
	int	i;

	i = 0;
	while (s[index] == c && s[index])
		index ++;
	while (s[index] != c && s[index])
	{
		i ++;
		index ++;
	}
	return (i);
}

static char	**free_all_str(char **out, int i)
{
	while (i > 0)
	{
		free(out[i]);
		i --;
	}
	free (out);
	return (out);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	int		l;
	int		i;
	int		j;
	char	**out;

	i = -1;
	j = 0;
	if (!s)
		return (NULL);
	n = get_size(s, c);
	out = (char **) malloc ((n + 1) * sizeof(char *));
	if (out == NULL)
		return (NULL);
	while (++ i < n)
	{
		l = get_len_str(s, c, j);
		out[i] = (char *) malloc ((l + 1) * sizeof(char));
		if (out[i] == NULL)
			return (free_all_str(out, i));
		get_str(&out[i][0], s, c, &j);
	}
	out[i] = NULL;
	return (out);
}
