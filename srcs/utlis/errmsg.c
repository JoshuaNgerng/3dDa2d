/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:52:23 by jngerng           #+#    #+#             */
/*   Updated: 2024/05/08 17:28:48 by jngerng          ###   ########.fr       */
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
	char			*ptr;
	static char		*fname;
	static size_t	len;

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
	if (s)
		write(2, s, len);
	if (!type)
		write(2, " cannot be opened: ", 19);
	if (type == 1)
		write(2, " cannot be read: ", 17);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}

void	errmsg_prog_errno(char type)
{
	char	*ptr;

	ptr = strerror(errno);
	write(2, BOLDRED "Error" RESET "\n" YELLOW, 25);
	if (!type)
		write(2, "Cannot initialize mlx library: ", 31);
	else if (type == 1)
		write(2, "Cannot allocate scene: ", 23);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}

void	errmsg_config(char type)
{
	write(2, BOLDRED "Error" RESET "\n" YELLOW, 25);
	if (!type)
		write(2, "No player in map", 16);
	else if (type == 1)
		write(2, "Duplicate player", 16);
	else if (type == 2)
		write(2, "Map not found", 13);
	else if (type == 3)
		write(2, "Invalid colour code 0 to 255 only", 33);
	write(2, RESET "\n", 5);
}

void	errmsg_config_var(char type, const char *msg, size_t len)
{
	write(2, BOLDRED "Error" RESET "\n" YELLOW, 25);
	if (!type)
		write(2, "Invalid map unknown character: ", 31);
	else if (type == 1)
		write(2, "Invalid delimiter for trbg: ", 28);
	if (msg)
		write(2, msg, len);
	if (type == 1)
		write(2, ", expected ','", 14);
	write(2, RESET "\n", 5);
}

void	errmsg_config_errno(char type)
{
	char	*ptr;

	ptr = strerror(errno);
	write(2, BOLDRED "Error" RESET "\n" YELLOW, 25);
	if (!type)
		write(2, "Cannot initialize mlx library: ", 31);
	else if (type == 1)
		write(2, "Cannot allocate scene: ", 23);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}

void	errmsg_config_errno_var(char type, const char *msg, size_t len)
{
	char	*ptr;

	write(2, BOLDRED "Error" RESET "\n" YELLOW, 25);
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (!type)
		write(2, ", cannot be opened: ", 20);
	ptr = strerror(errno);
	if (errno)
		write(2, ptr, len);
	write(2, RESET "\n", 5);
	errno = 0;
}
