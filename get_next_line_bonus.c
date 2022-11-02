/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:43:27 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/11/02 11:48:56 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*clean_buf(t_gnl *gnl)
{
	gnl->buf_size = 0;
	if (gnl->buf != NULL)
	{
		free(gnl->buf);
		gnl->buf = NULL;
	}
	return (NULL);
}

char	*fuck_lines(t_gnl *gnl, int read_result)
{
	if (read_result < 0)
		return (clean_buf(gnl));
	return (final_buf(gnl));
}

char	*read_from_file(t_gnl *gnl, int fd)
{
	char	*tmp;
	int		read_size;

	tmp = (char *) malloc (BUFFER_SIZE + 1);
	if (tmp == NULL)
		return (clean_buf(gnl));
	tmp[0] = '\0';
	while (has_new_line(tmp) < 0)
	{
		read_size = read (fd, tmp, BUFFER_SIZE);
		if (read_size <= 0)
		{
			free(tmp);
			return (fuck_lines(gnl, read_size));
		}
		tmp[read_size] = '\0';
		if (ft_join(gnl, tmp, read_size))
		{
			free(tmp);
			return (clean_buf(gnl));
		}
	}
	free(tmp);
	return (get_string(gnl, fd));
}

char	*get_string(t_gnl *gnl, int fd)
{
	int		line;

	line = 0;
	if (gnl->buf != NULL)
	{
		line = has_new_line(gnl->buf);
		if (line >= 0)
		{
			if (line + 1 == gnl->buf_size)
				return (final_buf(gnl));
			return (reset_buf(gnl, line));
		}
	}
	return (read_from_file(gnl, fd));
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl[1024];
	char			*result;

	result = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0)
		result = get_string(&gnl[fd], fd);
	return (result);
}
