/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:20:34 by cobecque          #+#    #+#             */
/*   Updated: 2018/09/16 17:57:47 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_all_malloc		*create_other_arena(t_all_malloc *all)
{
	t_all_malloc	*new;

	if (!(new = mmap(0, g_all_malloc.arena_size, PROT_READ | PROT_WRITE, 
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	new->next = all;
	all->prev = new;
	new->prev = NULL;
	g_all_malloc.first = new;
	return (new);
}

void		*ft_init_tiny(size_t size)
{
	void			*ret;

	if (!(g_all_malloc.tiny_malloc = mmap(0, g_all_malloc.tiny_malloc_element, PROT_READ |
					PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (!(ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
					-1, 0)))
		return (NULL);
	g_all_malloc.tiny_malloc->content_size = size;
	g_all_malloc.tiny_malloc->content = ret;
	printf("tiny %lu\n", g_all_malloc.tiny_malloc->content_size);
	return (ret);
}

void		*ft_init_small(size_t size)
{
	void			*ret;

	if (!(g_all_malloc.small_malloc = mmap(0, g_all_malloc.small_malloc_element, PROT_READ |
					PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (!(ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
					-1, 0)))
		return (NULL);
	g_all_malloc.small_malloc->content_size = size;
	g_all_malloc.small_malloc->content = ret;
	printf("small %lu\n", g_all_malloc.small_malloc->content_size);
	return (ret);
}

void		*ft_init_others(size_t size)
{
	void			*ret;

	g_all_malloc.others_malloc_size = size;
	if (!(g_all_malloc.others_malloc = mmap(0, g_all_malloc.others_malloc_size, PROT_READ | 
					PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (!(ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
					-1, 0)))
		return (NULL);
	g_all_malloc.others_malloc->content_size = size;
	g_all_malloc.others_malloc->content = ret;
	printf("other %lu\n", g_all_malloc.others_malloc->content_size);
	return (ret);
}

void		ft_init_all()
{
	size_t		page_size;

	page_size = INIT_PAGE;
	g_all_malloc.arena_size = page_size;
	g_all_malloc.tiny_malloc_size = page_size;
	g_all_malloc.small_malloc_size = page_size * 16;
	g_all_malloc.tiny_malloc_element = g_all_malloc.tiny_malloc_size / 64;
	g_all_malloc.small_malloc_element = g_all_malloc.small_malloc_size / 64;
}

void		*malloc(size_t size)
{
	t_all_malloc	*all;
	void			*plage;

	plage = NULL;
	if (g_all_malloc.tiny_malloc_size == 0)
	{
		ft_init_all();
		if (!(all = mmap(0, g_all_malloc.arena_size, PROT_READ | PROT_WRITE,
						MAP_ANON | MAP_PRIVATE, -1, 0)))
			return (NULL);
		g_all_malloc.first = all;
	}
	if (all->size_use > g_all_malloc.arena_size)
		all = create_other_arena(all);
	if (size <= g_all_malloc.tiny_malloc_element)
		plage = ft_init_tiny(size);
	else if (size <= g_all_malloc.small_malloc_element)
		plage = ft_init_small(size);
	else if (size > g_all_malloc.small_malloc_element)
		plage = ft_init_others(size);
	printf("size is %lu\n", size);
	return (plage);
}

int		main(void)
{
	char	*yolo;
	int		i;
	int		j;

	i = 0;
	j = 1025;
	yolo = (char *)malloc(sizeof(char) * j);
	while (i < j - 1)
	{
		yolo[i] = 'a';
		i++;
	}
	yolo[i] = '\0';
	printf("yolo = %s\n", yolo);
	return (0);
}
