/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:33:07 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 03:13:10 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		clear_area_small(uint8_t *addr, uint16_t size)
{
	int			i;

	i = 0;
	*(addr - 2) |= 0x80;
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
}

static void		clear_area_tiny(uint8_t *addr, uint16_t size)
{
	int			i;

	i = 0;
	*(addr - 2) |= 0x80;
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
}

uint8_t			*get_next(uint8_t *tmp, uint8_t *addr, int type)
{
	uint64_t	next;

	next = read_size(tmp);
	while (next != 0)
	{
		if (addr >= tmp - type && addr <= tmp - type + read16in8(tmp - type))
			break ;
		tmp = (uint8_t *)next + type;
		next = read_size(tmp);
	}
	return (tmp - type);
}

uint8_t			*delet_mem(uint8_t *free_this, uint64_t bef, int val, int nb)
{
	uint8_t		*tmp;

	tmp = (uint8_t *)bef;
	put_u64inu8(tmp + val, read_u64inu8(free_this + val));
	munmap(free_this, g_all_malloc.size_page * nb);
	g_all_malloc.g_count -= nb;
	return (tmp);
}

void			clear_area(uint8_t *addr)
{
	uint16_t		size;
	uint8_t			*tmp;

	tmp = check_type_of_malloc(addr);
	if (tmp == g_all_malloc.tiny)
		size = read16in8_block(addr - 2);
	else if (tmp == g_all_malloc.small)
		size = read16in8_block(addr - 2);
	else
		size = read_u64inu8(addr - 8);
	if (size <= g_all_malloc.tiny_size)
	{
		clear_area_tiny(addr, size);
		free_area_tiny((uint8_t *)g_all_malloc.tiny);
	}
	else if (size <= g_all_malloc.small_size)
	{
		clear_area_small(addr, size);
		free_area_small((uint8_t *)g_all_malloc.small);
	}
}
