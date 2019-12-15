/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 03:03:04 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		check_small_size(size_t size)
{
	uint8_t		*tmp;
	uint32_t	size_in_page;

	tmp = go_to_last_header_small((uint8_t *)g_all_malloc.small);
	size_in_page = read32in8(tmp);
	if (size_in_page + size + 2 < g_all_malloc.size_page * NBPAGE_SMALL)
		return (1);
	return (-1);
}

static uint8_t	*creat_block_small(uint8_t *ptr, uint32_t size)
{
	uint32_t	val;
	uint8_t		*tmp;

	put_u32inu8(ptr, size + read32in8(ptr) + 2);
	tmp = ptr + SIZE_HEADER_SMALL;
	val = read16in8_block(tmp);
	while (val != 0)
	{
		tmp += val + 2;
		val = read16in8_block(tmp);
	}
	put_u16inu8(tmp, size);
	return ((uint8_t*)(tmp + 2));
}

static uint8_t	*creat_new_area_small(size_t size)
{
	uint8_t	*area;

	area = mmap(0, g_all_malloc.size_page * NBPAGE_SMALL, \
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_all_malloc.g_count += NBPAGE_SMALL;
	if (area == MAP_FAILED)
		return (NULL);
	write_next_area_addr_small((uint64_t)area, (uint8_t *)g_all_malloc.small);
	put_u32inu8(area, size + SIZE_HEADER_SMALL + 2);
	put_u64inu8(area + 4, 0);
	put_u16inu8(area + SIZE_HEADER_SMALL, size);
	area += SIZE_HEADER_SMALL + 2;
	return (area);
}

void			*creat_small(uint16_t size)
{
	uint8_t		*area;

	if (g_all_malloc.small == NULL)
	{
		g_all_malloc.small = mmap(0, g_all_malloc.size_page * NBPAGE_SMALL,\
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_all_malloc.g_count += NBPAGE_SMALL;
		area = g_all_malloc.small;
		if (area == MAP_FAILED)
			return (NULL);
		put_u32inu8(area, size + SIZE_HEADER_SMALL + 2);
		put_u64inu8(area + 4, 0);
		put_u16inu8(area + SIZE_HEADER_SMALL, size);
		area += SIZE_HEADER_SMALL + 2;
	}
	else if (check_small_size(size) == -1)
		area = creat_new_area_small(size);
	else
	{
		area = go_to_last_header_small((uint8_t *)g_all_malloc.small);
		area = creat_block_small(area, size);
	}
	return (area);
}
