/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:40:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/13 17:16:53 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	put_large(uint8_t *addr, uint8_t *end, uint64_t size)
{
	ft_putstr("0x");
	ft_puthex((unsigned long)(addr + 16));
	ft_putstr(" - 0X");
	ft_puthex((unsigned long)(end));
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

int			print_tiny(void)
{
	uint8_t		*addr;
	uint16_t	size;
	uint64_t	tmp;
	int			total;

	addr = g_all_malloc.tiny;
	tmp = read_size(addr + 2);
	size = read16in8_block(addr + SIZE_HEADER);
	total = 0;
	while (tmp != 0 || size != 0)
	{
		tmp = read_size(addr + 2);
		addr += 10;
		while (size != 0)
		{
			total += print_block_tiny(addr, size);
			addr += size + 2;
			size = read16in8_block(addr);
		}
		addr = (uint8_t *)tmp;
		if (tmp != 0)
			size = read16in8_block(addr + SIZE_HEADER);
	}
	return (total);
}

int			print_small(void)
{
	uint8_t		*addr;
	uint16_t	size;
	uint64_t	tmp;
	int			total;

	addr = g_all_malloc.small;
	tmp = read_size(addr + 4);
	size = read16in8_block(addr + SIZE_HEADER_SMALL);
	total = 0;
	while (tmp != 0 || size != 0)
	{
		tmp = read_size(addr + 4);
		addr += SIZE_HEADER_SMALL;
		while (size != 0)
		{
			total += print_block_small(addr, size);
			addr += size + 2;
			size = read16in8_block(addr);
		}
		addr = (uint8_t *)tmp;
		if (tmp != 0)
			size = read16in8_block(addr + SIZE_HEADER_SMALL);
	}
	return (total);
}

int			print_large(void)
{
	uint8_t		*end;
	uint8_t		*addr;
	uint64_t	size;
	uint64_t	tmp;
	int			total;

	addr = g_all_malloc.large;
	tmp = read_size(addr + 8);
	size = read_u64inu8(addr);
	total = 0;
	while (tmp != 0 || size != 0)
	{
		tmp = read_size(addr + 8);
		size = read_u64inu8(addr);
		total += (size - 16);
		end = addr + size + 16;
		put_large(addr, end, size - 16);
		addr = (uint8_t *)tmp;
		size = 0;
		if (tmp != 0)
			size = read_u64inu8(addr);
	}
	return (total);
}
