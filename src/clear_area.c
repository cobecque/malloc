/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:33:07 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/10 17:21:02 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

uint8_t					*get_next(uint8_t *tmp, uint8_t *addr, int type)
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

static void				clear_area_tiny(uint8_t *addr, uint16_t size)
{
	uint8_t		*tmp;
	int			i;

	i = 0;
	tmp = (uint8_t *)g_all_malloc.tiny;
	tmp = get_next(tmp + 2, addr, 2);
	put_u16inu8(tmp, read16in8(tmp) - size - 2);
	*(addr - 2) |= 0x80;
	ft_putstr("Clear addr : ");
	ft_puthex((uint64_t)addr);
	ft_putchar('\n');
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
	if ((*(addr + i) & 0x80) == 0x80)
	{
		put_u16inu8(addr - 2, read16in8_block(addr + i) + \
				read16in8_block(addr - 2) + 2);
		*(addr - 2) |= 0x80;
		put_u16inu8(addr + i, 0);
	}
}

static void				clear_area_small(uint8_t *addr, uint16_t size)
{
	uint8_t		*tmp;
	int			i;

	i = 0;
	tmp = (uint8_t *)g_all_malloc.small;
	tmp = get_next(tmp + 4, addr, 4);
	put_u32inu8(tmp, read32in8(tmp) - size - 2);
	*(addr - 2) |= 0x80;
	/*ft_putstr("Clear addr : ");
	ft_puthex((uint64_t)addr);
	ft_putchar('\n');*/
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
	if ((*(addr + i) & 0x80) == 0x80)
	{
		put_u16inu8(addr - 2, read16in8_block(addr + i) + \
				read16in8_block(addr - 2) + 2);
		*(addr - 2) |= 0x80;
		put_u16inu8(addr + i, 0);
	}
}

static void				clear_area_large(uint8_t *addr, uint64_t size)
{
	uint64_t	next;
	uint8_t		*tmp;
	uint64_t	i;

	i = 0;
	tmp = (uint8_t *)g_all_malloc.large;
	tmp += 8;
	next = read_size(tmp);
	while (next != 0)
	{
		if (addr >= tmp - 8 && addr <= tmp - 8 + read_u64inu8(tmp - 8))
			break ;
		tmp = (uint8_t *)next + 8;
		next = read_size(tmp);
	}
	tmp -= 8;
	put_u64inu8(tmp, read_u64inu8(tmp) - size - 8);
	*(addr - 8) |= 0x80;
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
}

void					clear_area(uint8_t *addr)
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
	else
	{
		clear_area_large(addr, read_u64inu8(addr - 8));
		free_area_large((uint8_t *)g_all_malloc.large, addr);
	}
}
