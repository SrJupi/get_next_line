/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:30:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/08/09 13:03:43 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		has_new_line(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*reset_buf(char *buf, int nl)
{
	char	*str;
	int		i;
	
	i = 0;
	str = (char *) malloc (BUFFER_SIZE);
	while (*(buf + nl))
	{
		str[i] = buf[nl];
		i++;
		nl++;
	}
//	printf("reset -> str: %s\n-> buf: %s\n", str, buf);
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*result;
	int				new_line;
	int				i;

//	printf("gnl ->  %s\n", buf);
	
	i = 0;
	result = NULL;
	if (buf == NULL)
	{
		buf = (char *) malloc (BUFFER_SIZE);
		read(fd, buf, BUFFER_SIZE);
	}
	new_line =  has_new_line(buf);
	if (new_line >= 0)
	{
		result = (char *) malloc (new_line);
		while (i < new_line)
		{
			result[i] = buf[i];
			i++;
		}
		result[i] = '\0';
		buf = reset_buf(buf, new_line + 1);
//		printf("pos reset -> %s\n", buf);
	}
	//printf("%d\n", new_line);
	return (result);
}

