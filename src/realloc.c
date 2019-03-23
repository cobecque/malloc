/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:40:21 by cobecque          #+#    #+#             */
/*   Updated: 2019/03/09 19:32:12 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					check_type_size(size_t size, uint16_t s)
{
	if (s == 1 && size < g_all_malloc.tiny_size)
		return (1);
	else if (s == 2 && size < g_all_malloc.small_size && size >= \
			g_all_malloc.tiny_size)
		return (1);
	else if (s == 8 && size >= g_all_malloc.small_size)
		return (1);
	else
		return (-1);
}

static uint16_t		get_size_type(void *ptr, uint8_t *header)
{
	uint16_t	s;

	header = check_type_of_malloc(ptr);
	if (header == NULL)
		return (0);
	if (header == g_all_malloc.tiny)
		s = 1;
	else if (header == g_all_malloc.small)
		s = 2;
	else
		s = 8;
	return (s);
}

static int			nb_page(uint16_t s)
{
	if (s == 2)
		return (16);
	return (2);
}


void				*add_new_malloc(uint8_t *addr, size_t size)
{
	void	*ret;
	uint8_t *header;
	uint64_t s;

	header = NULL;
	ret = malloc(size);
	s = get_size_type(addr, header);
	if (s == 1)
		s = *(addr - 1);
	else if (s == 2)
		s = read16in8_block(addr - 2);
	else
		s = read_u64inu8(addr - 8);
	if (s < size)
		ret = ft_memcpy(ret, addr, s);
	else
		ret = ft_memcpy(ret, addr, size);
	free(addr);
	return (ret);
}

//1024
//1024 * 32
//1024 * 1024 
			// * 16
			// * 128

void				*realloc(void *ptr, size_t size)
{
	uint8_t		*header;
	uint8_t		*t;
	uint16_t	s;
	uint64_t	tmp;
	uint16_t	val;

	ft_putstr("coucou realloc\n");
	header = NULL;
	if (ptr == NULL)
		return (malloc(size));
	t = (uint8_t *)ptr;
	s = get_size_type(ptr, header);
	if (s == 0)
		return (NULL);
	if (check_type_size(size, s) == -1)
		return (add_new_malloc((uint8_t *)ptr, size));
	val = val_for_addr(t - s, s);
	tmp = (uint64_t)(t + val);
	t = (uint8_t *)tmp;
	if (s == 8)
		return (add_new_malloc((uint8_t *)ptr, size));
	if (val_for_addr((uint8_t *)t, s) == 0 && (uint64_t)(ptr - s + size) < \
			(uint64_t)(g_all_malloc.size_page * nb_page(s) + header))
	{
		pthread_mutex_lock(&mutex);
		return (ptr);
		pthread_mutex_unlock(&mutex);
	}
	else
		return (add_new_malloc((uint8_t *)ptr, size));
	return (NULL);
}
