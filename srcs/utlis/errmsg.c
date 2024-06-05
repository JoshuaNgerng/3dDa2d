/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:31 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 18:33:22 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	errmsg_prog(char type)
{
	write(2, BOLDRED "Error" RESET "\n" RED, 25);
	if (!type)
		write(2, "Invalid arguments, require only one argument "
			"as the file with .cub extension", 76);
	else if (type == 1)
		write(2, "File have wrong extension, expected .cub", 40);
	write(2, RESET "\n", 5);
}

void	errmsg_file_errno(char type, const char *s)
{
	char				*ptr;
	static const char	*fname;
	static size_t		len;

	if (!fname)
	{
		fname = s;
		len = ft_strlen(s);
		return ;
	}
	ptr = strerror(errno);
	write(2, BOLDRED "Error" RESET "\n" RED, 25);
	if (type >= 0 && type < 2)
		write(2, "File ", 5);
	if (fname)
		write(2, fname, len);
	if (!type)
		write(2, " cannot be opened: ", 19);
	if (type == 1)
		write(2, " cannot be read (get_next_line): ", 33);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}

void	errmsg_prog_errno(const char *msg, size_t len)
{
	char	*ptr;

	ptr = strerror(errno);
	write(2, BOLDRED "Error" RESET "\n" RED, 25);
	write(2, msg, len);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}
