/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:13:35 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/10/18 12:00:41 by lsulzbac         ###   ########.fr       */
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
			free(gnl->buf);
			gnl->buf = buf_tmp;
			buf_tmp = 0;
		}
	}
	return (tmp);
}

void	ft_clean(char **str)
{
	if (*str != NULL)
	{
		free (*str);
		*str = NULL;
	}
}

void	ft_join(t_gnl *gnl, char *str, int size)
{
	int		i;
	char	*tmp;
	
	tmp = NULL;
	printf("~~~~~~~~~~~~\ntmp: %s - size: %d\nbuf: %s - size: %d\n",
		str, size, gnl->buf, gnl->buf_size);
//	if (gnl->buf == NULL)
//	{
//		gnl->buf = str;
//		ft_clean(&str);
//		str = NULL;
//		gnl->buf_size += size;
//	}
//	else
//	{
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
		ft_clean(&str);
		gnl->buf = tmp;
		gnl->buf_size += size;
//	}
}

char	*read_from_file(t_gnl *gnl, int fd)
{
	char	*tmp;
	int		new_line;
	int		read_size;
	int		inside_while;

	tmp = NULL;
	inside_while = 0;
	new_line = -1;
	while (new_line < 0)
	{
		tmp = (char *) malloc (BUFFER_SIZE + 1);
		if (tmp != NULL)
		{
//			printf("\ninside while: %d\n", inside_while);
			read_size = read (fd, tmp, BUFFER_SIZE);
			if (read_size <= 0)
			{
//				printf("~~~~~~~~~~~~\nnew line: %d\ntmp: %s\nbuf: %s\n",
//					new_line, tmp, gnl->buf);
				gnl->has_finished = 1;
				break ;
			}
			tmp[read_size] = '\0';
			new_line = has_new_line(tmp);
			ft_join(gnl, tmp, read_size);
//			printf("**********\nnew line: %d\ntmp: %s\nbuf: %s\n",
//				new_line, tmp, gnl->buf);
			inside_while++;
		}
	}
//	ft_clean(&tmp);
//	printf("**********\nnew line: %d\ntmp: %s\nbuf: %s\n",
//		new_line, tmp, gnl->buf);
	return (get_line(gnl, fd));
}

char	*get_line(t_gnl *gnl, int fd)
{
	int		line;

	line = 0;
	if (gnl->buf != NULL)
	{
//		printf("\n**********\nif get_line\nbuf: %s, size: %d, finished: %d\n",
//				gnl->buf, gnl->buf_size, gnl->has_finished);
		line = has_new_line(gnl->buf);
		if (line >= 0)
			return (reset_buf(gnl, line));
		if (gnl->has_finished)
			return (final_buf(gnl));
	}
	if (gnl->has_finished)
		return (NULL);
//	printf("read line\n");
	return (read_from_file(gnl, fd));
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*result;

	result = NULL;
//	gnl.buf = "teste\nfinal";
//	gnl.buf_size = 11;
//	gnl.has_finished = 0;
	printf("antes: %s - size %d\n", gnl.buf, gnl.buf_size);
//	printf("fd %d: %d -> ", fd, gnl.buf_size);
	if (fd >= 0 && BUFFER_SIZE > 0)
		result = get_line(&gnl, fd);
//	printf("%d\n",gnl.buf_size);
	printf("depois: %s - size %d\n", gnl.buf, gnl.buf_size);
	return (result);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	if (argc == 1)
		fd = open ("test.txt", O_RDONLY);
	else
		fd = open (argv[1], O_RDONLY);
//	if (fd > 0)
//		str = get_next_line(fd);
	while (i < 10)
	{
		str = get_next_line(fd);
		printf("%d - %s\n", i, str);
		free(str);
		i++;
	}
	return (1);
}
