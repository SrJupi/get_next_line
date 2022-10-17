/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:13:35 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/10/17 14:07:25 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		has_new_line(char *str, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (str[i] == '\n')
			return i;
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

	tmp = (char *) malloc (new_line + 1);
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
//			free(gnl->buf);
			gnl->buf = buf_tmp;
			buf_tmp = 0;
		}
	}
	return (tmp);
}

char	*read_from_file(t_gnl *gnl, int fd)
{
	(void)gnl;
	(void)fd;
	return (NULL);
}

char	*get_line(t_gnl *gnl, int fd)
{
	int		line;

	line = 0;
	if (gnl->buf != NULL)
	{
		line = has_new_line(gnl->buf, gnl->buf_size);
		if (line >= 0)
			return (reset_buf(gnl, line));
		if (gnl->has_finished)
			return (final_buf(gnl));
	}
	return (read_from_file(gnl, fd));
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*result;

	result = NULL;
	gnl.buf = "teste\nfinal";
	gnl.buf_size = 11;
	gnl.has_finished = 0;
	printf("antes: %s - size %d\n", gnl.buf, gnl.buf_size);
//	printf("fd %d: %d -> ", fd, gnl.buf_size);
	if (fd >= 0)
		result = get_line(&gnl, fd);
//	printf("%d\n",gnl.buf_size);
	printf("depois: %s - size %d\n", gnl.buf, gnl.buf_size);
	return (result);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	str = NULL;
	if (argc == 1)
		fd = open ("test.txt", O_RDONLY);
	else
		fd = open (argv[1], O_RDONLY);
	if (fd > 0)
		str = get_next_line(fd);
	printf("1 - %s\n", str);
	return (1);
}
