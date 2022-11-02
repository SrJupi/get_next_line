/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:55:52 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/11/02 11:56:02 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	ft_strcpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*reset_buf(t_gnl *gnl, int new_line)
{
	char	*tmp;
	char	*buf_tmp;

	tmp = (char *) malloc (new_line + 2);
	if (tmp == NULL)
		return (clean_buf(gnl));
	buf_tmp = (char *) malloc (gnl->buf_size - new_line);
	if (buf_tmp == NULL)
	{
		free(tmp);
		return (clean_buf(gnl));
	}
	ft_strcpy(tmp, gnl->buf, new_line + 1);
	ft_strcpy(buf_tmp, gnl->buf + new_line + 1,
		gnl->buf_size - new_line - 1);
	gnl->buf_size -= (new_line + 1);
	free(gnl->buf);
	gnl->buf = buf_tmp;
	buf_tmp = NULL;
	return (tmp);
}

int	ft_join(t_gnl *gnl, char *str, int size)
{
	int		i;
	char	*tmp;

	tmp = (char *) malloc (gnl->buf_size + size + 1);
	if (tmp == NULL)
		return (1);
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
	free(gnl->buf);
	gnl->buf = tmp;
	gnl->buf_size += size;
	return (0);
}
