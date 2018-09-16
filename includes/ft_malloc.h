/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:39:33 by cobecque          #+#    #+#             */
/*   Updated: 2018/09/16 17:57:48 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#define INIT_PAGE 4096

typedef struct			s_list_malloc
{
	size_t				content_size;
	void				*content;
	void				*next;
	void				*prev;
}						t_list_malloc;

typedef struct			s_all_malloc
{
	t_list_malloc		*tiny_malloc;
	t_list_malloc		*small_malloc;
	t_list_malloc		*others_malloc;
	size_t				arena_size;
	size_t				size_use;
	size_t				tiny_malloc_size;
	size_t				small_malloc_size;
	size_t				others_malloc_size;
	size_t				tiny_malloc_element;
	size_t				small_malloc_element;
	int					nb_tiny;
	int					nb_small;
	int					nb_others;
	void				*first;
	void				*next;
	void				*prev;
}						t_all_malloc;

extern t_all_malloc g_all_malloc;

t_all_malloc g_all_malloc = {
						NULL,
						NULL,
						NULL,
						0,
						0,
						0,
						0,
						0,
						0,
						0,
						0,
						0,
						0,
						NULL,
						NULL,
						NULL,
};

void		*malloc(size_t size);
void		*get_tiny_alloc(size_t size);

#endif
