/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:40:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/08 08:50:09 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			print_block_tiny(uint8_t *addr, uint8_t size)
{
	uint8_t		*end;

	end = addr + size;
	printf("0x%lX - 0x%lX : %u octets\n", (unsigned long)(addr + 1), \
			(unsigned long)(end + 1), size);
	return (size);
}

int			print_block_small(uint8_t *addr, uint16_t size)
{
	uint8_t		*end;

	end = addr + size;
	printf("0x%lX - 0x%lX : %lu octets\n", (unsigned long)(addr + 1), \
		(unsigned long)(end + 1), (unsigned long)size);
	return (size);
}

int			print_tiny(void)
{
	uint8_t		*addr;
	uint8_t		size;
	uint64_t	tmp;
	int			total;

	addr = g_all_malloc.tiny;
	tmp = read_size(addr + 2);
	size = *(addr + 10);
	total = 0;
	while (tmp != 0 || size != 0)
	{
		tmp = read_size(addr + 2);
		addr += 10;
		while (size != 0)
		{
			total += print_block_tiny(addr, size);
			addr += size + 1;
			size = *(addr);
		}
		addr = (uint8_t *)tmp;
		if (tmp != 0)
			size = *(addr + 10);
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
	tmp = read_size(addr + 2);
	size = read16in8(addr + 10);
	total = 0;
	while (tmp != 0 || size != 0)
	{
		tmp = read_size(addr + 2);
		addr += 10;
		while (size != 0)
		{
			total += print_block_small(addr, size);
			addr += size + 2;
			size = read16in8(addr);
		}
		addr = (uint8_t *)tmp;
		if (tmp != 0)
			size = read16in8(addr + 10);
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
	total = 0;
	while (tmp != 0)
	{
		tmp = read_size(addr + 8);
		addr += 16;
		size = read_u64inu8(addr);
		total += size;
		end = addr + size;
		printf("0x%lX - 0x%lX : %lu octets\n", (unsigned long)(addr + 1), \
				(unsigned long)(end + 1), (unsigned long)size);
		addr = (uint8_t *)tmp;
	}
	return (total);
}
