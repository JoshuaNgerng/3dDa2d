/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:52:23 by jngerng           #+#    #+#             */
/*   Updated: 2024/03/18 18:14:44 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	errmsg(char type)
{
	write(2, BOLDRED "Error" RESET "\n" BOLDYELLOW, 28);
	if (!type)
		write(2, "Invalid arguments, require only one argument "
			"as the file with .cub extension", 76);
	else if (type == 1)
		write(2, "File have wrong extension, expected .cub", 40);
	else if (type == 2)
		write(2, "Invalid map player not found", 28);
	write(2, RESET "\n", 5);
}

void	errmsg_var(char type, const char *msg)
{
	write(2, BOLDRED "Error" RESET "\n" BOLDYELLOW, 28);
	if (!type)
		write(2, "Invalid map unknown character: ", 31);
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, RESET "\n", 5);
}

void	errmsg_errno(char type)
{
	char	*ptr;

	ptr = strerror(errno);
	write(2, BOLDRED "Error" RESET "\n" BOLDYELLOW, 28);
	if (!type)
		write(2, "Cannot allocate scene: ", 23);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
}

void	errmsg_errno_var(char type, const char *msg)
{
	char	*ptr;

	write(2, BOLDRED "Error" RESET "\n" BOLDYELLOW, 28);
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (!type)
		write(2, ", cannot be opened: ", 20);
	ptr = strerror(errno);
	if (errno)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}
