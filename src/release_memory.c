/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:04:19 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/12 06:04:04 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				pasdinspi(uint8_t *tmp, uint64_t next)
{
	if (tmp - 4 == g_all_malloc.small)
	{
		if (next != 0)
			g_all_malloc.small = (void *)(next - 4);
		else
			return (-1);
	}
	return (1);
}

void			free_area_small(uint8_t *addr)
{
	uint8_t		*tmp;
	uint8_t		*free_this;
	uint64_t	before;
	uint64_t	next;

	tmp = addr + 4;
	next = read_size(tmp);
	before = (uint64_t)tmp;
	while (1)
	{
		if (read32in8(tmp - 4) - 12 == 0)
		{
			free_this = tmp;
			if (pasdinspi(tmp, next) == -1)
				break ;
			tmp = (uint8_t *)before;
			put_u64inu8(tmp, read_u64inu8(free_this));
			munmap(free_this - 4, g_all_malloc.size_page * NBPAGE_SMALL);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 4;
		next = read_size(tmp);
	}
}

void			free_area_tiny(uint8_t *addr)
{
	uint8_t		*tmp;
	uint8_t		*free_this;
	uint64_t	before;
	uint64_t	next;

	tmp = addr + 2;
	next = read_size(tmp);
	before = (uint64_t)tmp;
	while (1)
	{
		if (read16in8(tmp - 2) - 10 == 0)
		{
			free_this = tmp;
			if ((uint64_t)tmp == before)
				g_all_malloc.tiny = (void *)read_size(tmp);
			tmp = (uint8_t *)before;
			put_u64inu8(tmp, read_u64inu8(free_this));
			munmap(free_this, g_all_malloc.size_page * NBPAGE_TINY);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 2;
		next = read_size(tmp);
	}
}

static uint8_t	*help_free_area_large(uint8_t *tmp, uint64_t before, uint64_t s)
{
	uint8_t		*free_this;

	free_this = tmp;
	if ((uint64_t)tmp == before)
		g_all_malloc.large = (void *)read_u64inu8(tmp);
	tmp = (uint8_t *)before;
	put_u64inu8(tmp, read_u64inu8(free_this));
	munmap(free_this, s);
	return (tmp);
}

void			free_area_large(uint8_t *header, uint8_t *addr)
{
	uint8_t		*tmp;
	uint64_t	before;
	uint64_t	next;
	uint64_t	size;

	tmp = header + 8;
	next = read_size(tmp);
	size = read_u64inu8(tmp - 8);
	before = (uint64_t)tmp;
	while (next != 0 || size != 0)
	{
		size = read_u64inu8(tmp - 8);
		if (read_u64inu8(tmp - 8) - 16 == 0 && tmp - 8 == addr - 24)
			tmp = help_free_area_large(tmp, before, size);
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 8;
		next = read_size(tmp);
	}
}
