/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:19 by jngerng           #+#    #+#             */
/*   Updated: 2023/03/15 10:51:28 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_buffer(char *out, char *buffer, int r)
{
	char	*temp;

	if (r >= 0 && r <= BUFFER_SIZE)
		buffer[r] = '\0';
	else
		return (NULL);
	if (!out && !*buffer)
		return (NULL);
	if (!out)
		out = ft_strjoin(buffer, "");
	else
	{
		temp = out;
		out = ft_strjoin(out, buffer);
		free(temp);
	}
	return (out);
}

static char	*read_from_file(int fd, char *stored, int *index, int *err)
{
	int		r;
	char	*out;
	char	*buffer;

	out = stored;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (set_err(err), NULL);
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		out = join_buffer(out, buffer, r);
		*index = 0;
		if (ft_sp_strchr(out, '\n', index))
			break ;
		if (!out)
			return (free(buffer), set_err(err), NULL);
		r = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (r == -1)
		return (set_err(err), free(out), NULL);
	return (out);
}

static char	*get_line(char *buffer, int n, int *err)
{
	int		i;
	char	*out;

	i = -1;
	if (n == 0)
		return (NULL);
	out = (char *) malloc ((n + 1) * sizeof(char));
	if (!out)
		return (set_err(err), NULL);
	while (++ i < n && buffer[i])
		out[i] = buffer[i];
	out[i] = '\0';
	return (out);
}

static char	*refresh(char *buffer, int n, int *err)
{
	char	*out;

	out = NULL;
	if (!buffer)
		return (NULL);
	if (!buffer[n])
		return (free(buffer), NULL);
	if (buffer[n])
		out = ft_strjoin(&buffer[n], "");
	free(buffer);
	if (!out)
		return (set_err(err), NULL);
	return (out);
}

int	get_next_line(int fd, char **output)
{
	int			err;
	int			len;
	static char	*buffer[1024];

	len = 0;
	err = 0;
	if (!output)
		return (0);
	*output = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (1);
	if (ft_sp_strchr(buffer[fd], '\n', &len))
	{
		*output = get_line(buffer[fd], len, &err);
		buffer[fd] = refresh(buffer[fd], len, &err);
		return (err);
	}
	buffer[fd] = read_from_file(fd, buffer[fd], &len, &err);
	if (!buffer[fd])
		return (err);
	if (len == 0)
		ft_sp_strchr(buffer[fd], '\n', &len);
	*output = get_line(buffer[fd], len, &err);
	buffer[fd] = refresh(buffer[fd], len, &err);
	return (err);
}
