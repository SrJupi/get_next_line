/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:13:44 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/10/19 17:33:30 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct gnl_struct {
	char	*buf;
	int		buf_size;
	int		has_finished;
}	t_gnl;

int		has_new_line(char *str);
char	*final_buf(t_gnl *gnl);
char	*reset_buf(t_gnl *gnl, int new_line);
char	*get_next_line(int fd);
char	*get_line(t_gnl *gnl, int fd);
char	*read_from_file(t_gnl *gnl, int fd);
void	ft_join(t_gnl *gnl, char *str, int size);
void	ft_strcpy(char *dst, char *src, int size);


#endif
