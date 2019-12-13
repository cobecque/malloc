/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:38:44 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/13 22:41:28 by rostroh          ###   ########.fr       */
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
	else*/
	if (jump_next == 8)
	{
		look_up -= 8;
		/*ft_putstr("Look for addr : ");
		ft_puthex((uint64_t)look_up);
		ft_putchar('\n');*/
		val = read_u64inu8(look_up);
	}
	return (val);
}

int				look_addr(uint8_t *look_up, uint8_t *to_find, uint16_t size, uint16_t type)
{
	uint8_t			*last;
	uint16_t		val;
	int				wtf;

	if (size == 8)
	{
		wtf = size;
		size = type;
		type = wtf;
	}
	look_up += 8;
	if (look_up + size == to_find)
	{
		if ((*look_up & 0x80) == 0x80)
		{
			return (0);
		}
		return (1);
	}
	look_up += size;
/*	ft_putstr("Apres size = ");
	ft_putnbr(size);
	ft_putstr(" et type = ");
	ft_putnbr(type);
	ft_putchar('\n');*/
	val = val_for_addr(look_up, type);
	/*ft_putstr("val = ");
	ft_putnbr(val);
	ft_putchar('\n');*/
	while (val != 0)
	{
		last = look_up;
		look_up += val + size;/*
		ft_puthex((uint64_t)look_up);
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

int				free_large(uint8_t *addr, uint8_t *current)
{
	uint64_t		tmp;
	uint64_t		size;
	uint8_t			*old;

	old = NULL;
	//ft_putstr("Ici pour free du large\n");
	tmp = read_u64inu8(current + 8);
	size = read_u64inu8(current);
	if (current == addr - 16)
	{
		if (addr - 16 == g_all_malloc.large)
		{
			current = (uint8_t *)tmp;
			tmp = read_u64inu8(current + 8);
			if (tmp != 0)
				g_all_malloc.large = current;
			else
				g_all_malloc.large = NULL;
		}
		//ft_putstr("Et de une zone free\n");
		munmap(addr, size);
		return (0);
	}
	while (tmp != 0)
	{
		current = (uint8_t *)tmp;
		tmp = read_u64inu8(current + 8);
		size = read_u64inu8(current);
		/*ft_putstr("current = ");
		ft_puthex((uint64_t)current);
		ft_putstr(", next = ");
		ft_puthex((uint64_t)tmp);
		ft_putstr(" et size current = ");
		ft_putnbr(size);
		ft_putchar('\n');*/
		if (current == addr - 16)
		{
			if (old != NULL)
				put_u64inu8(old + 8, read_u64inu8(current + 8));
			//ft_putstr("Et de une zone free\n");
			munmap(addr, size);
			return (0);
		}
		old = current;
	}
//	ft_putstr("Y A R POTO\n\n");
	return (0);
}

int				is_allocated(uint8_t *addr)
{
	uint64_t		tmp;
	uint8_t			*current;
	uint16_t		size;
	uint16_t		jump;

//	ft_putstr("non pas toi is allocated\n");
	current = check_type_of_malloc(addr);
/*	ft_putstr("current: ");
	ft_puthex((unsigned long)current);
	ft_putchar('\n');*/
	if (current == 0)
		return (0);
	get_size_jump(&size, &jump, current);
	if (jump == 8)
		return (free_large(addr, current));
	if (jump == 8)
		current += jump;
	else
		current += size;
	tmp = read_size(current);/*
	ft_putstr("tmp: ");
	ft_puthex(tmp);
	ft_putstr(" et current: ");
	ft_puthex((unsigned long)current);
	ft_putchar('\n');
	ft_putstr("Avant size = ");
	ft_putnbr(size);
	ft_putstr(" et jump = ");
	ft_putnbr(jump);
	ft_putchar('\n');*/
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
