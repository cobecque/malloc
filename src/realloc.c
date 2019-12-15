/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:00:04 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/15 19:07:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*add_new_malloc(uint8_t *addr, size_t size)
{
	void		*ret;
	uint8_t		*header;
	uint64_t	s;

	header = NULL;
	ret = malloc(size);
	s = get_size_type(addr, &header);
	if (s == 2)
		s = read16in8_block(addr - 2);
	else if (s == 3)
		s = read16in8_block(addr - 2);
	else
		s = read_u64inu8(addr - 16);
	if (s < size)
		ret = ft_memcpy(ret, addr, s);
	else
		ret = ft_memcpy(ret, addr, size);
	free(addr);
	return (ret);
}

static void			help_realloc(uint8_t **t, uint64_t val)
{
	uint64_t	tmp;

	tmp = (uint64_t)(*t + val);
	*t = (uint8_t *)tmp;
}

static int			check_type_size_rea(size_t size, uint16_t *s)
{
	if (*s == 2 && size < g_all_malloc.tiny_size)
		return (1);
	else if (*s == 3 && size < g_all_malloc.small_size && size >= \
			g_all_malloc.tiny_size)
	{
		*s = 2;
		return (1);
	}
	else if (*s == 8 && size >= g_all_malloc.small_size)
		return (1);
	else
		return (-1);
}

void				*realloc(void *ptr, size_t size)
{
	uint8_t		*header;
	uint8_t		*t;
	uint16_t	s;
	uint64_t	val;

	header = NULL;
	if (ptr == NULL)
		return (malloc(size));
	t = (uint8_t *)ptr;
	s = get_size_type(ptr, &header);
	if (s == 0)
		return (NULL);
	if (check_type_size_rea(size, &s) == -1)
		return (add_new_malloc((uint8_t *)ptr, size));
	if (s == 8)
		return (add_new_malloc((uint8_t *)ptr, size));
	else
		val = val_for_addr_new(t - s, s);
	help_realloc(&t, val);
	if (size <= read16in8_block(ptr - 2))
		return (ptr);
	else
		return (add_new_malloc((uint8_t *)ptr, size));
	return (NULL);
}
