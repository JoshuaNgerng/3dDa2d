/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:33:36 by jngerng           #+#    #+#             */
/*   Updated: 2024/06/03 18:33:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	else if (type == 4)
		write(2, "Map have no close borders (1)", 29);
	else if (type == 5)
		write(2, "Invalid character after element identifier", 42);
	write(2, RESET "\n", 5);
}

void	errmsg_config_var(char type, const char *msg, size_t len)
{
	write(2, BOLDRED "Error" RESET "\n" YELLOW, 25);
	if (!type)
		write(2, "Invalid character in map: ", 26);
	else if (type == 1)
		write(2, "Invalid delimiter for trbg colour code: ", 40);
	if (msg)
		write(2, msg, len);
	if (type == 1)
		write(2, ", expected `,'", 14);
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
		write(2, "Cannot make mlx windows: ", 25);
	else if (type == 2)
		write(2, "Cannot make mlx image for scene: ", 33);
	else if (type == 3)
		write(2, "Cannot make mlx image for minimap: ", 35);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}

void	errmsg_img(const char *msg, size_t len)
{
	char	*ptr;

	write(2, BOLDRED "Error" RESET "\nImage, " YELLOW, 32);
	if (msg)
		write(2, msg, len);
	write(2, ", cannot be made in mlx: ", 25);
	ptr = strerror(errno);
	if (errno)
		write(2, ptr, ft_strlen(ptr));
	write(2, RESET "\n", 5);
	errno = 0;
}
