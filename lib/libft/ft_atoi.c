/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:35:27 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/18 14:10:17 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		sign;
	int		total;

	total = 0;
	sign = 1;
	while ((*(char *)str >= 9 && *(char *)str <= 13) || *(char *)str == 32)
		str ++;
	if (*(char *)str == '-' || *(char *)str == '+')
	{
		if (*(char *)str == '-')
			sign *= -1;
		str ++;
	}
	while (*(char *)str >= '0' && *(char *)str <= '9')
	{
		total = total * 10 + *str - 48;
		str ++;
	}
	return (total * sign);
}
