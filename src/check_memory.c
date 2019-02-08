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

	val = read16in8(look_up - 1);
	if (jump_next == 2)
		val = read16in8(look_up);
	else if (jump_next == 8)
		val = read_u64inu8(look_up);
	return (val);
}

int			look_addr(uint8_t *look_up, uint8_t *to_find, uint16_t size)
{
	uint8_t			*last;
	uint16_t		val;
	int				jump_next;

	jump_next = 8;
	if (size < g_all_malloc.tiny_size)
		jump_next = 1;
	else if (size < g_all_malloc.small_size)
		jump_next = 2;
	look_up += 8;
	if (look_up + jump_next == to_find)
		return (1);
	val = val_for_addr(look_up, jump_next);
	while (val != 0)
	{
		last = look_up;
		look_up += val + jump_next;
		if (look_up + jump_next == to_find)
			return (1);
		val = val_for_addr(look_up, jump_next);
	}
	return (0);
}

int			is_allocated(uint8_t *addr)
{
	uint64_t		tmp;
	uint8_t			*current;
	uint16_t		size;

	size = read16in8(addr - 2);
	current = g_all_malloc.large;
	if (size < g_all_malloc.tiny_size)
		current = g_all_malloc.tiny;
	else if (size < g_all_malloc.small_size)
		current = g_all_malloc.small;
	if (current == 0 || size == 0)
		return (0);
	current += 2;
	if (size >= g_all_malloc.small_size)
		current += 6;
	tmp = read_size(current);
	while (tmp != 0)
	{
		current = (uint8_t *)tmp + 2;
		if (size >= g_all_malloc.small_size)
			current = (uint8_t *)tmp + 8;
		if ((uint64_t)current < (uint64_t)addr && (uint64_t)addr < tmp)
			return (look_addr(addr, current, size));
		tmp = read_size(current);
	}
	return (look_addr(current, addr, size));
}
