/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:45 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 16:39:39 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_size(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	if (n >= 10)
	{
		i += get_size(n / 10);
		n %= 10;
	}
	if (n < 10)
		i += 1;
	return (i);
}

static int	get_base(int n, int size)
{
	int	base;

	base = 1;
	if (n < 0)
		size --;
	while (size > 1)
	{
		base *= 10;
		size --;
	}
	return (base);
}

static char	*ft_strcpy(char *dest, char *src)
{
	char	*buffer;

	buffer = dest;
	while (*src)
	{
		*buffer = *src;
		buffer ++;
		src ++;
	}
	*buffer = '\0';
	return (dest);
}

static char	*get_number(char *input, int n, int size)
{
	int	i;
	int	base;

	i = 0;
	base = get_base(n, size);
	if (n == -2147483648)
	{
		input = ft_strcpy(input, "-2147483648");
		return (input);
	}
	if (n < 0)
	{
		input[i] = '-';
		n = -n;
		i ++;
	}
	while (base >= 1)
	{
		input[i] = n / base + '0';
		i ++;
		n %= base;
		base /= 10;
	}
	input[i] = '\0';
	return (input);
}

char	*ft_itoa(int n)
{
	int		s;
	char	*ptr;

	s = get_size(n);
	ptr = (char *)malloc((s + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr = get_number(ptr, n, s);
	return (ptr);
}
