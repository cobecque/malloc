/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:38:44 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/13 18:02:57 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

uint16_t		val_for_addr(uint8_t *look_up, int jump_next)
{
	uint16_t	val;

	val = 0;
	val = read16in8_block(look_up);
	/*if (jump_next == 4)
		val = read32in8_block(look_up);
	else*/ if (jump_next == 8)
		val = read_u64inu8(look_up);
	return (val);
}

int				look_addr(uint8_t *look_up, uint8_t *to_find, uint16_t size, uint16_t type)
{
	uint8_t			*last;
	uint16_t		val;

	ft_putstr("lol\n");
	look_up += 8;
	if (look_up + size == to_find)
	{
		if ((*look_up & 0x80) == 0x80)
			return (0);
		return (1);
	}
	look_up += size;
	val = val_for_addr(look_up, type);
	while (val != 0)
	{
		last = look_up;
		look_up += val + size;
		/*ft_puthex((uint64_t)look_up);
		ft_putstr(" avec une size de ");
		ft_putnbr(val);
		ft_putstr(" next -> ");*/
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
		*size = -8;
	}
}

int				is_allocated(uint8_t *addr)
{
	uint64_t		tmp;
	uint8_t			*current;
	uint16_t		size;
	uint16_t		jump;

	ft_putstr("non pas toi is allocated\n");
	current = check_type_of_malloc(addr);
	ft_putstr("current: ");
	ft_puthex((unsigned long)current);
	ft_putchar('\n');
	if (current == 0)
		return (0);
	get_size_jump(&size, &jump, current);
	if (jump == 8)
		current += jump;
	else
		current += size;
	tmp = read_size(current);
	ft_putstr("tmp: ");
	ft_puthex(tmp);
	ft_putstr(" et current: ");
	ft_puthex((unsigned long)current);
	ft_putchar('\n');
	while (tmp != 0)
	{
		if ((uint64_t)current < (uint64_t)addr && (uint64_t)addr < tmp)
			return (look_addr(current, addr, jump, size));
		if (jump == 8)
			current = (uint8_t *)tmp + jump;
		else
			current = (uint8_t *)tmp + size;
		tmp = read_size(current);
	}
	return (look_addr(current, addr, jump, size));
}
