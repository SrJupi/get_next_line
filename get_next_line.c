/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:30:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/08/10 12:56:35 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

int		has_new_line(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '\n')
		{
		//	printf("--> %s <--\n", str);
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*reset_buf(char *buf, int nl)
{
	char	*str;
	int		i;
	
	if (ft_strlen(buf) == nl)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	str = (char *) malloc (BUFFER_SIZE);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, BUFFER_SIZE);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	r = (char *) malloc (s1_len + s2_len + 1);
	if (r != NULL)
	{
		ft_bzero(r, s1_len + s2_len + 1);
		while (s1[i])
		{
			r[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i])
		{
			r[i + s1_len] = s2[i];
			i++;
		}
		r[i + s1_len] = '\0';
	}
	return (r);
}

char	*read_from_file(char *buf, int fd)
{
	char	*new_buf;
	char	*join_word;
	int		read_result;

	new_buf = (char *) malloc (BUFFER_SIZE);
	if (new_buf == NULL)
		return (NULL);
	ft_bzero(new_buf, BUFFER_SIZE);
	read_result = read(fd, new_buf, BUFFER_SIZE);
	if (read_result <= 0)
	{
		free(new_buf);
		return (NULL);
	}
	if (buf == NULL)
		return (new_buf);
	join_word = ft_strjoin(buf, new_buf);
//	printf("buf: %s\nnew buf: %s\njoin: %s\n", buf, new_buf, join_word);
	free(buf);
	free(new_buf);
	return (join_word);

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
		buf = read_from_file(buf, fd);
		if (buf == NULL)
			return (NULL);
	}
	new_line =  has_new_line(buf);
	if (new_line >= 0)
	{
		result = (char *) malloc (new_line);
		if (result == NULL)
			return (NULL);
		ft_bzero(result, new_line);
		while (i < new_line)
		{
			result[i] = buf[i];
			i++;
		}
		result[i] = '\0';
	//	printf("pre reset -> %s\n***********************\n", buf);
		buf = reset_buf(buf, new_line + 1);
	//	printf("pos reset -> %s\n~~~~~~~~~~~~~~~~~~~~~~~\n", buf);
	}
	else
	{
		buf = read_from_file(buf, fd);
		result = get_next_line(fd);
	}
	//printf("%d\n", new_line);
	return (result);
}

