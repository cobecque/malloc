/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/08 07:43:03 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_small_size(size_t size)
{
	uint8_t		*tmp;
	int			size_in_page;

	tmp = go_to_last_header((uint8_t *)g_all_malloc.small);
	size_in_page = read16in8(tmp);
	if (size_in_page + size + 2 < g_all_malloc.size_page * 16)
		return (1);
	return (-1);
}

uint8_t			*creat_block_small(uint8_t *ptr, uint16_t size)
{
	uint16_t	val;
	uint8_t		*tmp;

	put_u16inu8(ptr, size + read16in8(ptr) + 2);
	tmp = ptr + SIZE_HEADER;
	val = read16in8(tmp);
	while (val != 0)
	{
		tmp += val + 2;
		val = read16in8(tmp);
	}
	put_u16inu8(tmp, size);
	val = read16in8(tmp);
	return ((uint8_t*)(tmp + 2));
}

uint8_t			*creat_new_area_small(size_t size)
{
	uint8_t	*area;

	area = mmap(0, g_all_malloc.size_page * 16, \
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	write_next_area_addr((uint64_t)area, (uint8_t *)g_all_malloc.small);
	creat_header((uint16_t *)area);
	put_u16inu8(area, size + SIZE_HEADER + 2);
	put_u16inu8(area + SIZE_HEADER, size);
	area += 2;
	return (area);
}

void			*creat_small(uint16_t size)
{
	uint8_t		*area;

	if (g_all_malloc.small == NULL)
	{
		g_all_malloc.small = mmap(0, g_all_malloc.size_page * 16,\
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		area = g_all_malloc.small;
		if (area == MAP_FAILED)
			return (NULL);
		creat_header((uint16_t*)area);
		put_u16inu8(area, size + SIZE_HEADER + 2);
		put_u16inu8(area + SIZE_HEADER, size);
		area += 2;
	}
	else if (check_small_size(size) == -1)
		area = creat_new_area_small(size);
	else
	{
		area = go_to_last_header((uint8_t *)g_all_malloc.small);
		area = creat_block_small(area, size);
	}
	return (area);
}
