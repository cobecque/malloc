/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 22:44:02 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/15 20:08:55 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*check_list(int fd, t_list *lst)
{
	t_fd	*new;

	if (lst->content && ((t_fd *)lst->content)->fd == fd)
		return (lst);
	else if (lst->next)
		return (check_list(fd, lst->next));
	else
	{
		if (!(new = (t_fd *)malloc(sizeof(t_fd))))
			return (0);
		new->fd = fd;
		new->curr = new->buf + BUFF_SIZE;
		ft_bzero(new->buf, BUFF_SIZE + 1);
		if (!(lst->next = (t_list *)malloc(sizeof(t_list))))
			return (0);
		lst->next->next = 0;
		lst->next->content = new;
		return (lst->next);
	}
}

static int		ft_write(char **line, t_fd *current)
{
	char	*tmp;

	tmp = *line;
	*current->curr++ = '\0';
	if (!(*line = ft_strjoin(tmp, current->buf)))
		return (-1);
	free(tmp);
	return (1);
}

static int		check_line(char **line, t_fd *current)
{
	char	*tmp;
	char	*tmp_line;

	tmp_line = *line;
	if ((tmp = ft_strchr(current->curr, '\n')))
	{
		*tmp = '\0';
		if (!(*line = ft_strjoin(*line, current->curr)))
			return (-1);
		free(tmp_line);
		current->curr = tmp + 1;
		return (1);
	}
	if (!(*line = ft_strjoin(*line, current->curr)))
		return (-1);
	free(tmp_line);
	current->curr = current->buf + BUFF_SIZE;
	return (0);
}

static int		ft_get_line(char **line, int fd, t_fd *lst_fd)
{
	int	ret;
	int	tmp;

	tmp = 0;
	while ((ret = read(fd, lst_fd->buf, BUFF_SIZE)) > 0)
	{
		tmp = 1;
		lst_fd->buf[ret] = '\0';
		if ((lst_fd->curr = ft_strchr(lst_fd->buf, '\n')))
			return (ft_write(line, lst_fd));
		lst_fd->curr = lst_fd->buf + ret;
		if ((ft_write(line, lst_fd)) == -1)
			return (-1);
		lst_fd->curr = lst_fd->buf + ret;
	}
	return ((ret == -1) ? -1 : tmp);
}

int				get_next_line(int fd, char **line)
{
	static t_list	list;
	t_list			*lst_tmp;
	t_fd			*lst_fd;
	int				tmp;
	int				boolean;

	boolean = 0;
	if (!(lst_tmp = check_list(fd, &list)) || !line)
		return (-1);
	lst_fd = lst_tmp->content;
	if (!(*line = ft_strnew(0)))
		return (-1);
	if (*(lst_fd->curr))
	{
		if ((tmp = check_line(line, lst_fd)) || tmp == -1)
			return (tmp);
		boolean = 1;
	}
	if ((tmp = ft_get_line(line, fd, lst_fd)) != 0)
		return (tmp);
	free(lst_tmp->content);
	free(lst_tmp);
	return (boolean);
}
