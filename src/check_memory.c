/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:38:44 by cobecque          #+#    #+#             */
/*   Updated: 2019/02/19 00:45:35 by rostroh          ###   ########.fr       */
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

void		get_size_jump(uint16_t *size, uint16_t *jump, uint8_t *current)
{
	*size = 2;
	*jump = 1;
	if (current == g_all_malloc.small)
		*jump = 2;
	if (current == g_all_malloc.large)
	{
		*jump = 8;
		*size = 8;
	}
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
	get_size_jump(&size, &jump, current);
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
