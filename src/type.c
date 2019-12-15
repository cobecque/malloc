/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:44:09 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 02:32:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		check_block(uint8_t *header, uint8_t *find, int type)
{
	uint8_t		*addr;
	uint16_t	val;

	addr = header + SIZE_HEADER;
	if (type == 8)
		addr += 6;
	else if (type == 2)
		addr += 2;
	if (addr == find)
		return (1);
	if (type == 2 || type == 1)
	{
		val = read16in8_block(addr);
		while (val != 0)
		{
			if (addr > find)
				return (-1);
			if (addr + 2 == find)
				return (1);
			addr += val + 2;
			val = read16in8_block(addr);
		}
	}
	return (-1);
}

int				is_tiny_malloc(uint8_t *addr)
{
	uint8_t		*h;
	uint16_t	size;
	uint64_t	tmp;

	h = g_all_malloc.tiny;
	if (h == 0)
		return (-1);
	size = read16in8(h);
	tmp = read_size(h + 2);
	while (tmp != 0)
	{
		if (addr >= h && addr <= h + g_all_malloc.size_page * NBPAGE_TINY)
			return (check_block(h, addr, 1));
		h = (uint8_t *)tmp;
		tmp = read_size(h + 2);
	}
	if (addr >= h && addr <= h + g_all_malloc.size_page * NBPAGE_TINY)
		return (check_block(h, addr, 1));
	return (0);
}

int				is_small_malloc(uint8_t *addr)
{
	uint8_t		*h;
	uint16_t	size;
	uint64_t	tmp;

	h = g_all_malloc.small;
	if (h == NULL)
		return (-1);
	size = read16in8(h);
	tmp = read_size(h + 4);
	while (tmp != 0)
	{
		if (addr >= h && addr <= h + g_all_malloc.size_page * NBPAGE_SMALL)
			return (check_block(h, addr, 2));
		h = (uint8_t *)tmp;
		tmp = read_size(h + 4);
	}
	if (addr >= h && addr <= h + g_all_malloc.size_page * NBPAGE_SMALL)
		return (check_block(h, addr, 2));
	return (0);
}

int				is_large_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint64_t	size;
	uint64_t	tmp;

	header = g_all_malloc.large;
	if (header == 0)
		return (-1);
	size = read_u64inu8(header);
	tmp = read_u64inu8(header + 8);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + size)
			return (check_block(header, addr, 8));
		header = (uint8_t *)tmp;
		tmp = read_u64inu8(header + 8);
	}
	if (addr >= header && addr <= header + size)
		return (check_block(header, addr, 8));
	return (0);
}

uint8_t			*check_type_of_malloc(uint8_t *addr)
{
	if (is_tiny_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.tiny);
	else if (is_small_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.small);
	else if (is_large_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.large);
	else if (is_large_malloc(addr) == -1 && is_tiny_malloc(addr) == -1 \
			&& is_small_malloc(addr) == -1)
		return (NULL);
	return (NULL);
}
