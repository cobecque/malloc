/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:38:44 by cobecque          #+#    #+#             */
/*   Updated: 2019/02/08 09:43:50 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

uint16_t	val_for_addr(uint8_t *look_up, int jump_next)
{
	uint16_t	val;

	val = (*look_up) & 0x7f;
	if (jump_next == 2)
		val = read16in8_block(look_up);
	else if (jump_next == 8)
		val = read_u64inu8(look_up);
	return (val);
}

int			look_addr(uint8_t *look_up, uint8_t *to_find, uint16_t size)
{
	uint8_t			*last;
	uint16_t		val;

	look_up += 8;
	if (look_up + size == to_find)
	{
		if ((*look_up & 0x80) == 0x80)
			return (0);
		return (1);
	}
	val = val_for_addr(look_up, size);
	while (val != 0)
	{
		last = look_up;
		look_up += val + size;
		if (look_up + size == to_find)
		{
			if ((*look_up & 0x80) == 0x80)
				return (0);
			return (1);
		}
		val = val_for_addr(look_up, size);
	}
	return (0);
}

int			is_tiny_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint16_t	size;
	uint64_t	tmp;

	if (*(addr - 1) == 0)
		return (-1);
	header = g_all_malloc.tiny;
	if (header == 0)
		return (-1);
	size = read16in8(header);
	tmp = read_size(header + 2);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + g_all_malloc.size_page * 2)
			return (1);
		header = (uint8_t *)tmp;
		tmp = read_size(header + 2);
	}
	if (addr >= header && addr <= header + g_all_malloc.size_page * 2)
		return (1);
	return (0);
}

int			is_small_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint16_t	size;
	uint64_t	tmp;

	if (read16in8_block(addr - 2) == 0)
		return (-1);
	header = g_all_malloc.small;
	if (header == NULL)
		return (-1);
	size = read16in8(header);
	tmp = read_size(header + 2);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + g_all_malloc.size_page * 16)
			return (1);
		header = (uint8_t *)tmp;
		tmp = read_size(header + 2);
	}
	if (addr >= header && addr <= header + g_all_malloc.size_page * 16)
		return (1);
	return (0);
}

int			is_large_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint64_t	size;
	uint64_t	tmp;

	if (read_u64inu8(addr - 8) == 0)
		return (-1);
	header = g_all_malloc.large;
	if (header == 0)
		return (-1);
	size = read_u64inu8(header);
	tmp = read_u64inu8(header + 8);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + size)
			return (1);
		header = (uint8_t *)tmp;
		tmp = read_u64inu8(header + 8);
	}
	if (addr >= header && addr <= header + size)
		return (1);
	return (0);
}

uint8_t		*check_type_of_malloc(uint8_t *addr)
{
	if (is_tiny_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.tiny);
	else if (is_small_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.small);
	else if (is_large_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.large);
	else if (is_large_malloc(addr) == -1 && is_tiny_malloc(addr) == -1 && is_small_malloc(addr) == -1)
		return (NULL);
	return (NULL);
}

int			is_allocated(uint8_t *addr)
{
	uint64_t		tmp;
	uint8_t			*current;
	uint16_t		size;
	uint16_t		jump;

	current = check_type_of_malloc(addr);
	if (current == 0)
		return (0);
	size = 2;
	jump = 1;
	if (current == g_all_malloc.small)
		jump = 2;
	if (current == g_all_malloc.large)
	{
		jump = 8;
		size = 8;
	}
	current += size;
	tmp = read_size(current);
	while (tmp != 0)
	{
		if ((uint64_t)current < (uint64_t)addr && (uint64_t)addr < tmp)
			return (look_addr(current, addr, jump));
		current = (uint8_t *)tmp + size;
		tmp = read_size(current);
	}
	return (look_addr(current, addr, jump));
}
