/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/04/24 04:39:44 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

uint8_t			*creat_block(uint8_t *ptr, uint8_t size)
{
	uint8_t		*tmp;

	put_u16inu8(ptr, size + read16in8(ptr) + 1);
	tmp = ptr + SIZE_HEADER;
	while ((*tmp & 0x7f) != 0)
	{
		if (((*tmp & 0x80) == 0x80) && (*tmp & 0x7f) >= size)
		{
			*tmp = *tmp & 0x7f;
			return (tmp + 1);
		}
		tmp += (*tmp & 0x7f) + 1;
	}
	*tmp = size;
	return (tmp + 1);
}

int				check_tiny_size(size_t size)
{
	uint8_t		*tmp;
	int			size_in_page;

	tmp = go_to_last_header((uint8_t *)g_all_malloc.tiny);
	size_in_page = read16in8(tmp);
	if (size_in_page + size + 1 <= g_all_malloc.size_page * NBPAGE_TINY)
		return (1);
	return (-1);
}

uint8_t			*creat_new_area_tiny(uint8_t size)
{
	uint8_t	*area;

	area = mmap(0, getpagesize() * NBPAGE_TINY, PROT_READ | PROT_WRITE, \
			MAP_ANON | MAP_PRIVATE, -1, 0);
	write_next_area_addr((uint64_t)area, (uint8_t *)g_all_malloc.tiny);
	creat_header((uint16_t *)area, 1);
	put_u16inu8(area, size + SIZE_HEADER + 1);
	area += SIZE_HEADER;
	put_size_tiny(area, size);
	area++;
	return (area);
}

void			*creat_tiny(uint8_t size)
{
	uint8_t			*area;

	if (g_all_malloc.tiny == NULL)
	{
		g_all_malloc.tiny = mmap(0, g_all_malloc.size_page * NBPAGE_TINY, \
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		area = g_all_malloc.tiny;
		if (area == MAP_FAILED)
			return (NULL);
		creat_header((uint16_t*)area, 1);
		put_u16inu8(area, size + SIZE_HEADER + 1);
		area += SIZE_HEADER;
		put_size_tiny(area, size);
		area++;
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
