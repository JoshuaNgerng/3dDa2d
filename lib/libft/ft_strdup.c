/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 01:33:41 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 10:51:50 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*temp;
	char	*out;

	i = 0;
	temp = (char *)src;
	len = ft_strlen(temp);
	out = (char *)malloc((len + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	while (i < len)
	{
		out[i] = temp[i];
		i ++;
	}
	out[len] = '\0';
	return (out);
}
