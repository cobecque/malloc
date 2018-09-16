/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 00:59:06 by cobecque          #+#    #+#             */
/*   Updated: 2017/08/13 06:06:46 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 40

typedef struct		s_fd
{
	int				fd;
	char			buf[BUFF_SIZE + 1];
	char			*curr;
}					t_fd;

int					get_next_line(int fd, char **line);

#endif
