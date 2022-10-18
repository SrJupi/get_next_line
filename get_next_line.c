/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:57:25 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/10/18 12:48:43 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*final_buf(t_gnl *gnl)
{
	char	*tmp;

	tmp = gnl->buf;
	gnl->buf = NULL;
	gnl->buf_size = 0;
	return (tmp);
}

char	*reset_buf(t_gnl *gnl, int new_line)
{
	char	*tmp;
	char	*buf_tmp;
	int		i;

	if (gnl->buf_size == new_line + 1)
		return (final_buf(gnl));
	tmp = (char *) malloc (new_line + 2);
	i = 0;
	if (tmp != NULL)
	{
		while (i <= new_line)
		{
			tmp[i] = gnl->buf[i];
			i++;
		}
		tmp[i] = '\0';
		buf_tmp = (char *) malloc (gnl->buf_size - new_line + 1);
		if (buf_tmp != NULL)
		{
			while (i < gnl->buf_size)
			{
				buf_tmp[i - (new_line + 1)] = gnl->buf[i];
				i++;
			}
			buf_tmp[i - (new_line + 1)] = '\0';
			gnl->buf_size -= (new_line + 1);
			ft_clean(&gnl->buf);
			gnl->buf = buf_tmp;
			buf_tmp = NULL;
		}
	}
	return (tmp);
}

void	ft_clean(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free (*str);
		*str = NULL;
	}
}

void	ft_join(t_gnl *gnl, char *str, int size)
{
	int		i;
	char	*tmp;

	tmp = (char *) malloc (gnl->buf_size + size + 1);
	if (tmp != NULL)
	{
		i = 0;
		while (i < gnl->buf_size)
		{
			tmp[i] = gnl->buf[i];
			i++;
		}
		while (i < gnl->buf_size + size)
		{
			tmp[i] = str[i - gnl->buf_size];
			i++;
		}
		tmp[i] = '\0';
	}
	ft_clean(&gnl->buf);
	gnl->buf = tmp;
	gnl->buf_size += size;
}

char	*read_from_file(t_gnl *gnl, int fd)
{
	char	*tmp;
	int		new_line;
	int		read_size;

	tmp = NULL;
	new_line = -1;
	while (new_line < 0)
	{
		tmp = (char *) malloc (BUFFER_SIZE + 1);
		if (tmp != NULL)
		{
			read_size = read (fd, tmp, BUFFER_SIZE);
			if (read_size <= 0)
			{
				gnl->has_finished = 1;
				ft_clean(&tmp);
				break ;
			}
			tmp[read_size] = '\0';
			new_line = has_new_line(tmp);
			ft_join(gnl, tmp, read_size);
			ft_clean(&tmp);
		}
	}
	return (get_line(gnl, fd));
}

char	*get_line(t_gnl *gnl, int fd)
{
	int		line;

	line = 0;
	if (gnl->buf != NULL)
	{
		line = has_new_line(gnl->buf);
		if (line >= 0)
			return (reset_buf(gnl, line));
		else if (gnl->has_finished)
			return (final_buf(gnl));
	}
	if (gnl->has_finished)
		return (NULL);
	return (read_from_file(gnl, fd));
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*result;

	result = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0)
		result = get_line(&gnl, fd);
	return (result);
}
