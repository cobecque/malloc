/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:04:19 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 03:10:14 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		if_small(uint8_t *tmp, uint64_t next)
{
	if (tmp == g_all_malloc.small)
	{
		if (next != 0)
			g_all_malloc.small = (void *)(next);
		else
		{
			ft_bzero(g_all_malloc.small, g_all_malloc.size_page * NBPAGE_SMALL);
			put_u32inu8(g_all_malloc.small, SIZE_HEADER_SMALL);
			return (-1);
		}
	}
	return (1);
}

static int		if_tiny(uint8_t *tmp, uint64_t next)
{
	if (tmp == g_all_malloc.tiny)
	{
		if (next != 0)
			g_all_malloc.tiny = (void *)(next);
		else
		{
			ft_bzero(g_all_malloc.tiny, g_all_malloc.size_page * NBPAGE_TINY);
			put_u16inu8(g_all_malloc.tiny, SIZE_HEADER);
			return (-1);
		}
	}
	return (1);
}

int				is_full_free(uint8_t *addr, int type)
{
	uint8_t		*tmp;
	uint8_t		*tmp_addr;
	uint16_t	size;

	if (addr == 0)
		return (-1);
	tmp = addr + SIZE_HEADER + type;
	if (type == 0)
		tmp_addr = addr + read16in8(addr);
	else
		tmp_addr = addr + read32in8(addr);
	while (tmp < tmp_addr)
	{
		if ((*tmp & 0x80) != 0x80)
			return (-1);
		size = read16in8_block(tmp);
		tmp += size + 2;
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
	tmp -= 4;
	while (1)
	{
		if (is_full_free(tmp, 2) == 1)
		{
			free_this = tmp;
			if (if_small(tmp, next) == -1)
				break ;
			tmp = delet_mem(free_this, before, 4, NBPAGE_SMALL);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 4;
		next = read_size(tmp);
		tmp -= 4;
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
	tmp -= 2;
	while (1)
	{
		if (is_full_free(tmp, 0) == 1)
		{
			free_this = tmp;
			if (if_tiny(tmp, next) == -1)
				break ;
			tmp = delet_mem(free_this, before, 2, NBPAGE_TINY);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 2;
		next = read_size(tmp);
		tmp -= 2;
	}
}
