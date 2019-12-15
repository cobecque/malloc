/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:00:29 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/15 19:09:22 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static uint8_t	*creat_block(uint8_t *ptr, uint16_t size)
{
	uint32_t	val;
	uint8_t		*tmp;

	put_u16inu8(ptr, size + read16in8(ptr) + 2);
	tmp = ptr + SIZE_HEADER;
	val = read16in8_block(tmp);
	while (val != 0)
	{
		tmp += val + 2;
		val = read16in8_block(tmp);
	}
	put_u16inu8(tmp, size);
	return ((uint8_t*)(tmp + 2));
}

static int		check_tiny_size(uint16_t size)
{
	uint8_t		*tmp;
	uint16_t	size_in_page;

	tmp = go_to_last_header((uint8_t *)g_all_malloc.tiny);
	size_in_page = read16in8(tmp);
	if (size_in_page + size + 2 <= g_all_malloc.size_page * NBPAGE_TINY)
		return (1);
	return (-1);
}

static uint8_t	*creat_new_area_tiny(uint16_t size)
{
	uint8_t	*area;

	area = mmap(0, g_all_malloc.size_page * NBPAGE_TINY, PROT_READ | \
			PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_all_malloc.g_count += NBPAGE_TINY;
	write_next_area_addr((uint64_t)area, (uint8_t *)g_all_malloc.tiny);
	put_u16inu8(area, size + SIZE_HEADER + 2);
	put_u64inu8(area + 2, 0);
	put_u16inu8(area + SIZE_HEADER, size);
	area += SIZE_HEADER + 2;
	return (area);
}

void			*creat_tiny(uint16_t size)
{
	uint8_t			*area;

	if (g_all_malloc.tiny == NULL)
	{
		g_all_malloc.tiny = mmap(0, g_all_malloc.size_page * NBPAGE_TINY, \
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		area = g_all_malloc.tiny;
		g_all_malloc.g_count += NBPAGE_TINY;
		if (area == MAP_FAILED)
			return (NULL);
		put_u16inu8(area, size + SIZE_HEADER + 2);
		put_u64inu8(area + 2, 0);
		put_u16inu8(area + SIZE_HEADER, size);
		area += SIZE_HEADER + 2;
	}
	else if (check_tiny_size(size) == -1)
		area = creat_new_area_tiny(size);
	else
	{
		area = go_to_last_header((uint8_t *)g_all_malloc.tiny);
		area = creat_block(area, size);
	}
	return ((void *)(area));
}
