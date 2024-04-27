/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:15:40 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/19 11:15:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = ft_strlen(s);
	while (*(unsigned char *)(s + n) != (unsigned char)c && n != 0)
		n --;
	if (*(unsigned char *)(s + n) != (unsigned char)c && n == 0)
		return (NULL);
	return ((char *)(s + n));
}
