/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:40:21 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/24 23:02:55 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static uint16_t		get_size_type(void *ptr, uint8_t **header)
{
	uint16_t	s;
	uint64_t	next;

	*header = check_type_of_malloc(ptr);
	if (*header == NULL)
		return (0);
	s = 2;
	if (*header == g_all_malloc.large)
	{
		*header += 8;
		next = read_size(*header);
		while (next != 0)
		{
			if ((uint8_t *)ptr >= *header - 8 && (uint8_t *)ptr <= *header - 8 + read_u64inu8(*header - 8))
				break ;
			*header = (uint8_t *)next + 8;
			next = read_size(*header);
		}
		*header -= 8;
		s = 8;
	}
	else if (*header == g_all_malloc.small)
		*header = get_next(*header + 4, ptr, 4);
	else if (*header == g_all_malloc.tiny)
		*header = get_next(*header + 2, ptr, 2);
	return (s);
}

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
		// ft_putstr("large realloc : ");
		// ft_putnbr(nb);
		// ft_putchar('\n');
		return (nb);
	}
	return (NBPAGE_TINY);
}

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

uint64_t		val_for_addr_new(uint8_t *look_up, int jump_next)
{
	uint64_t	val;

	val = read16in8_block(look_up);
	if (jump_next == 8)
		val = read_u64inu8(look_up);
	return (val);
}

int			check_type_size_rea(size_t size, uint16_t s)
{
	if (s == 2 && size < g_all_malloc.tiny_size)
		return (1);
	else if (s == 2 && size < g_all_malloc.small_size && size >= \
			g_all_malloc.tiny_size)
		return (1);
	else if (s == 8 && size >= g_all_malloc.small_size)
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
	if (check_type_size_rea(size, s) == -1)
		return (add_new_malloc((uint8_t *)ptr, size));
	val = val_for_addr_new(t - s, s);
	help_realloc(&t, val);
	ft_putstr("realloc : ");
	ft_putnbr((uint64_t)(ptr - s + size));
	ft_putstr(" & ");
	ft_putnbr((uint64_t)(g_all_malloc.size_page * nb_page(s, ptr) + header));
	ft_putchar('\n');
	if (s == 8 && (uint64_t)(ptr - s + size) < (uint64_t)(g_all_malloc.size_page * nb_page(s, ptr) + header))
	 	return (ptr);
	else if (val_for_addr_new((uint8_t *)t, s) == 0 && (uint64_t)(ptr - s + size) < \
			(uint64_t)(g_all_malloc.size_page * nb_page(s, ptr) + header))
		return (ptr);
	else
		return (add_new_malloc((uint8_t *)ptr, size));
	return (NULL);
}
