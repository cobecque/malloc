/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/14 22:26:11 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static uint8_t	*creat_block(uint8_t *ptr, uint16_t size)
{
	uint32_t	val;
	uint8_t		*tmp;
//	uint8_t		*refac;

	put_u16inu8(ptr, size + read16in8(ptr) + 2);
	tmp = ptr + SIZE_HEADER;
	val = read16in8_block(tmp);
	while (val != 0)
	{
		/*if (((*tmp & 0x80) == 0x80))
		{
			ft_putstr("ta mere cette catin: ");
			ft_puthex((unsigned long)tmp);
			ft_putchar('\n');
			tmp = refactorisation(tmp, size);
			ft_putstr("cette catin elle est bien passer: ");
			ft_puthex((unsigned long)tmp);
			ft_putchar('\n');
			if (read16in8_block(tmp) == 0)
				break ;
			val = read16in8_block(tmp);
			tmp += val + 2;
			val = read16in8_block(tmp);
			ft_putstr("Et maintenant cette catin elle est ou : ");
			ft_puthex((unsigned long)tmp);
			ft_putchar('\n');
		}
		else
		{*/
			tmp += val + 2;
			val = read16in8_block(tmp);
		//}
	}/*
	ft_putstr("??? : ");
	ft_puthex((uint64_t)tmp);
	ft_putchar('\n');*/
	put_u16inu8(tmp, size);
	return ((uint8_t*)(tmp + 2));
}

static int		check_tiny_size(uint16_t size)
{
	uint8_t		*tmp;
	uint16_t	size_in_page;

	tmp = go_to_last_header((uint8_t *)g_all_malloc.tiny);
	size_in_page = read16in8(tmp);
	/*ft_putstr("size: ");
	ft_puthex((unsigned long)size);
	ft_putstr(" size_in_page: ");
	ft_puthex((unsigned long)size_in_page);
	ft_putstr(" et size total: ");
	ft_puthex((unsigned long)(g_all_malloc.size_page * NBPAGE_TINY));
	ft_putchar('\n');*/
	if (size_in_page + size + 2 <= g_all_malloc.size_page * NBPAGE_TINY)
		return (1);
	return (-1);
}

static uint8_t	*creat_new_area_tiny(uint16_t size)
{
	uint8_t	*area;

	area = mmap(0, g_all_malloc.size_page * NBPAGE_TINY, PROT_READ | PROT_WRITE, \
			MAP_ANON | MAP_PRIVATE, -1, 0);
	write_next_area_addr((uint64_t)area, (uint8_t *)g_all_malloc.tiny);
	ft_putstr("testing new header: ");
	ft_puthex(read_size(g_all_malloc.tiny + 2));
	ft_putchar('\n');
	//creat_header((uint16_t *)area, 1);
	/*ft_putstr("new area: ");
	ft_puthex((unsigned long)area);
	ft_putchar('\n');*/
	put_u16inu8(area, size + SIZE_HEADER + 2);
	put_u64inu8(area + 2, 0);
	put_u16inu8(area + SIZE_HEADER, size);
	area += SIZE_HEADER + 2;
	return (area);
}

void			*creat_tiny(uint16_t size)
{
	uint8_t			*area;

//	ft_putstr("size in tiny: ");
//	ft_putnbr(size);
//	ft_putchar('\n');
	if (g_all_malloc.tiny == NULL)
	{
		g_all_malloc.tiny = mmap(0, g_all_malloc.size_page * NBPAGE_TINY, \
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		area = g_all_malloc.tiny;
		if (area == MAP_FAILED)
			return (NULL);
		creat_header((uint16_t*)area, 1);
		put_u16inu8(area, size + SIZE_HEADER + 2);
		put_u64inu8(area + 2, 0);
		put_u16inu8(area + SIZE_HEADER, size);
		area += SIZE_HEADER + 2;
	}
	else if (check_tiny_size(size) == -1)
	{
	//	ft_putstr("\nnew area\n");
		area = creat_new_area_tiny(size);
	}
	else
	{
		//ft_putstr("flemme\n");
		area = go_to_last_header((uint8_t *)g_all_malloc.tiny);
	/*	ft_putstr("last area: ");
		ft_puthex((unsigned long)area);
		ft_putchar('\n');*/
		area = creat_block(area, size);
/*		ft_putstr("tmp  area: ");
		ft_puthex((unsigned long)area);
		ft_putchar('\n');*/
	}
	//ft_putstr("tiny base: ");
	//ft_puthex((unsigned long)g_all_malloc.tiny);
/*	ft_putstr(" salop de tiny je sais ou tu te caches: ");
	ft_puthex((unsigned long)area);
	ft_putstr(" avec ta size a la con: ");
	ft_putnbr(size);
	ft_putchar('\n');*/
	return ((void *)(area));
}
