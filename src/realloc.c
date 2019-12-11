/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:40:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/11 16:41:02 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
/*
static int			nb_page(uint16_t s, void *ptr)
{
	uint64_t	val;
	uint8_t		*header;
	int			nb;

	header = check_type_of_malloc(ptr);
	if (header == g_all_malloc.small)
		return (NBPAGE_SMALL);
	else if (header == g_all_malloc.large)
	{
		val = read_u64inu8(ptr - s);
		nb = val / g_all_malloc.size_page;
		if (val % g_all_malloc.size_page != 0)
			nb++;
		return (nb);
	}
	return (NBPAGE_TINY);
}
*/
static void			*add_new_malloc(uint8_t *addr, size_t size)
{
	void		*ret;
	uint8_t		*header;
	uint64_t	s;

	header = NULL;
	ret = malloc(size);
	s = get_size_type(addr, &header);
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

static void			help_realloc(uint8_t **t, uint64_t val)
{
	uint64_t	tmp;

	tmp = (uint64_t)(*t + val);
	*t = (uint8_t *)tmp;
}

int					check_type_size_rea(size_t size, uint16_t *s)
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

	header = NULL;/*
	ft_putstr("realloc: ");
	ft_puthex((unsigned long)ptr);
	ft_putstr(" sur une size: ");
	ft_putnbr(size);
	ft_putstr("\n\n");*/
	if (ptr == NULL)
		return (malloc(size));
	t = (uint8_t *)ptr;
	s = get_size_type(ptr, &header);
	if (s == 0)
		return (NULL);
	if (check_type_size_rea(size, &s) == -1)
		return (add_new_malloc((uint8_t *)ptr, size));
	val = val_for_addr_new(t - s, s);
	help_realloc(&t, val);
	if (s == 8 && size <= read_u64inu8(ptr - 8))
		return (ptr);
	/*if (s == 8 && (uint64_t)(ptr - s + size) < \
			(uint64_t)(g_all_malloc.size_page * nb_page(s, ptr) + header))
	{
		ft_putstr("2\n");
		return (ptr);
	}*/
	else if (size <= read16in8_block(ptr - 2))
		return (ptr);
	/*
	else if (val_for_addr_new((uint8_t *)t, s) == 0 && (uint64_t)(ptr - s + \
		size) < (uint64_t)(g_all_malloc.size_page * nb_page(s, ptr) + header))
	{
		ft_putstr("3\n");
		return (ptr);
	}*/
	else
		return (add_new_malloc((uint8_t *)ptr, size));
	//ft_putstr("Beuh?\n");
	return (NULL);
}
