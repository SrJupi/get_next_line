/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:56:13 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/11/02 11:56:17 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct gnl_struct {
	char	*buf;
	int		buf_size;
}	t_gnl;

int		has_new_line(char *str);
char	*final_buf(t_gnl *gnl);
char	*reset_buf(t_gnl *gnl, int new_line);
char	*get_next_line(int fd);
char	*get_string(t_gnl *gnl, int fd);
char	*read_from_file(t_gnl *gnl, int fd);
int		ft_join(t_gnl *gnl, char *str, int size);
void	ft_strcpy(char *dst, char *src, int size);
void	*clean_buf(t_gnl *gnl);

#endif
