/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:38:44 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/05 18:04:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

uint16_t		val_for_addr(uint8_t *look_up, int jump_next)
{
	uint16_t	val;

	val = 0;
	val = read16in8_block(look_up);
	if (jump_next == 4)
		val = read32in8_block(look_up);
	else if (jump_next == 8)
		val = read_u64inu8(look_up);
	return (val);
}

int				look_addr(uint8_t *look_up, uint8_t *to_find, uint16_t size, uint16_t type)
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
	val = val_for_addr(look_up, type);
	while (val != 0)
	{
		/*ft_putstr("\n\non crash ou look_up: ");
		ft_puthex((unsigned long)look_up);
		ft_putstr(" ou encore to find: ");
		ft_puthex((unsigned long)to_find);
		ft_putstr(" et avec la size: ");
		ft_putnbr(size);
		ft_putchar('\n');*/
		last = look_up;
		look_up += val + size;
		if (look_up + size == to_find)
		{
			if ((*look_up & 0x80) == 0x80)
				return (0);
			return (1);
		}
		val = val_for_addr(look_up, type);
	}
	return (0);
}

static void		get_size_jump(uint16_t *size, uint16_t *jump, uint8_t *current)
{
	*size = 2;
	*jump = 2;
	if (current == g_all_malloc.small)
		*size = 4;
	if (current == g_all_malloc.large)
	{
		*jump = 8;
		*size = 8;
	}
}

int				is_allocated(uint8_t *addr)
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
			return (look_addr(current, addr, jump, size));
		current = (uint8_t *)tmp + size;
		tmp = read_size(current);
	}
	return (look_addr(current, addr, jump, size));
}
