/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/12 22:37:20 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		check_small_size(size_t size)
{
	uint8_t		*tmp;
	uint32_t	size_in_page;

	tmp = go_to_last_header_small((uint8_t *)g_all_malloc.small);
	size_in_page = read32in8(tmp);
	if (size_in_page + size + 2 < g_all_malloc.size_page * NBPAGE_SMALL)
		return (1);
	return (-1);
}

static uint8_t	*creat_block_small(uint8_t *ptr, uint32_t size)
{
	uint32_t	val;
	uint8_t		*tmp;

	put_u32inu8(ptr, size + read32in8(ptr) + 2);
	tmp = ptr + SIZE_HEADER_SMALL;
	val = read16in8_block(tmp);
	while (val != 0)
	{
/*		ft_putstr("yolo dans le val: ");
		ft_puthex((unsigned long)tmp);
		ft_putstr(" avec bien sur la size: ");
		ft_puthex((unsigned long)val);
		ft_putchar('\n');*/
		/*if (((*tmp & 0x80) == 0x80))
		{
			tmp = refactorisation(tmp, size);
			if (read16in8_block(tmp) == 0)
				break ;
			val = read16in8_block(tmp);
			tmp += val + 2;
			val = read16in8_block(tmp);
		}
		else
		{*/
			/*ft_putstr("val dans creat small: ");
			ft_puthex((unsigned long)tmp);
			ft_putchar('\n');*/
			tmp += val + 2;
			val = read16in8_block(tmp);
		//}
	}
	put_u16inu8(tmp, size);
	return ((uint8_t*)(tmp + 2));
}

static uint8_t	*creat_new_area_small(size_t size)
{
	uint8_t	*area;

	area = mmap(0, g_all_malloc.size_page * NBPAGE_SMALL, \
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	write_next_area_addr_small((uint64_t)area, (uint8_t *)g_all_malloc.small);
	creat_header((uint16_t *)area, 2);
	put_u32inu8(area, size + SIZE_HEADER_SMALL + 2);
	put_u64inu8(area + 4, 0);
	put_u16inu8(area + SIZE_HEADER_SMALL, size);
	area += SIZE_HEADER_SMALL + 2;
	return (area);
}

uint8_t			*refactorisation(uint8_t *ptr, uint16_t size)
{
	uint16_t	new_size;
	uint16_t	old_size;

	/*
	ft_putstr("refact addr : ");
	ft_puthex((uint64_t)ptr);
	ft_putchar('\n');*/
	old_size = read16in8_block(ptr);
	new_size = old_size;
	ft_putstr("\n\n\n\nnew size = ");
	ft_putnbr(new_size);
	ft_putchar('\n');
	while ((*(ptr + old_size + 2) & 0x80) == 0x80)
	{
		new_size = read16in8_block(ptr + old_size + 2);
		if (old_size + new_size > SIZE_MAX_UINT16)
			break;
		old_size += new_size;
		ft_putstr("\nsize while = ");
		ft_putnbr(old_size);
		ft_putchar('\n');
		put_u16inu8(ptr, old_size);
		put_u16inu8(ptr + old_size, 0);
	}
	new_size = read16in8_block(ptr);
	if (size < new_size)
	{
		put_u16inu8(ptr + size + 2, new_size - size - 2);
		put_u16inu8(ptr, 0);
		ft_putstr("\nsize reussit malloc = ");
		ft_putnbr(new_size - size - 2);
		ft_putchar('\n');
	}
	return (ptr);
}
/*
uint8_t			*refactorisation(uint8_t *ptr, uint16_t size)
{
	uint16_t	old_size;

	ft_putstr("refac ");
	ft_puthex((uint64_t)ptr);
	ft_putchar('\n');
	old_size = read16in8_block(ptr);
	ft_putstr("old size = ");
	ft_putnbr(old_size);
	ft_putstr("   size = ");
	ft_putnbr(size);
	ft_putchar('\n');
	put_u16inu8(ptr, size);
	if (old_size - size - 2 < 0)
		put_u16inu8(ptr + size + 2, 0);
	else
		put_u16inu8(ptr + size + 2, (old_size - size - 2));
	ft_putstr("Write : ");
	ft_putnbr(old_size - size - 2);
	ft_putstr(" a ");
	ft_puthex((uint64_t)(ptr + size + 2));
	ft_putchar('\n');
	if ((*(ptr + size + 2) & 0x80) == 0x80)
	{
		ft_putstr("alright\n");
		*(ptr + size + 2) |= 0x80;
	}
	return (ptr + 2);
}*/

void			*creat_small(uint16_t size)
{
	uint8_t		*area;

//	ft_putstr("size dans small: ");
//	ft_putnbr(size);
//	ft_putchar('\n');
	if (g_all_malloc.small == NULL)
	{
		g_all_malloc.small = mmap(0, g_all_malloc.size_page * NBPAGE_SMALL,\
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		area = g_all_malloc.small;
		if (area == MAP_FAILED)
			return (NULL);
		creat_header((uint16_t*)area, 4);
		put_u32inu8(area, size + SIZE_HEADER_SMALL + 2);
		put_u64inu8(area + 4, 0);
		put_u16inu8(area + SIZE_HEADER_SMALL, size);
		area += SIZE_HEADER_SMALL + 2;
	}
	else if (check_small_size(size) == -1)
		area = creat_new_area_small(size);
	else
	{
		area = go_to_last_header_small((uint8_t *)g_all_malloc.small);
		/*ft_putstr("ici sur le dernier: ");
		ft_puthex((unsigned long)area);
		ft_putchar('\n');*/
		area = creat_block_small(area, size);
/*		ft_putstr("et l'addr : ");
		ft_puthex((unsigned long)area);
		ft_putstr(" la size: ");
		ft_puthex((unsigned long)read16in8_block(area - 2));
		ft_putchar('\n');*/
	}
/*	ft_putstr("salop de small je sais ou tu te caches: ");
	ft_puthex((unsigned long)area);
	//ft_putstr(" avec ta size a la con: ");
	//ft_putnbr(size);
	ft_putchar('\n');*/
	return (area);
}
