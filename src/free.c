/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:33:07 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/08 09:38:05 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		clear_area_tiny(uint8_t *addr, uint16_t size)
{
	uint64_t	next;
	uint8_t		*tmp;
	int			i;

	i = 0;
	tmp = (uint8_t *)g_all_malloc.tiny;
	tmp += 2;
	next = read_size(tmp);
	while (next != 0)
	{
		if (addr >= tmp - 2 && addr <= tmp - 2 + read16in8(tmp - 2))
			break ;
		tmp = (uint8_t *)next + 2;
		next = read_size(tmp);
	}
	tmp -= 2;
	put_u16inu8(tmp, read16in8(tmp) - size - 1);
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
}

void		clear_area_small(uint8_t *addr, uint16_t size)
{
	uint64_t	next;
	uint8_t		*tmp;
	int			i;

	i = 0;
	tmp = (uint8_t *)g_all_malloc.small;
	tmp += 2;
	next = read_size(tmp);
	while (next != 0)
	{
		if (addr >= tmp - 2 && addr <= tmp - 2 + read16in8(tmp - 2))
			break ;
		tmp = (uint8_t *)next + 2;
		next = read_size(tmp);
	}
	tmp -= 2;
	put_u16inu8(tmp, read16in8(tmp) - size - 2);
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
}

void		clear_area_large(uint8_t *addr, uint64_t size)
{
	uint64_t	next;
	uint8_t		*tmp;
	int			i;

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
	while (i < size)
	{
		addr[i] = 0;
		i++;
	}
}

void		clear_area(uint8_t *addr)
{
	uint16_t		size;
	uint64_t		next;
	uint8_t			*tmp;

	size = read16in8(addr - 2);
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

void		free(void *ptr)
{
	uint8_t		*addr;

	if (!ptr)
		exit(0);
	addr = (uint8_t*)ptr;
	if (is_allocated(addr) == 0)
		printf("PHILLIPE JE SAIS OU TU TE CACHES !\n");
	else
		clear_area(addr);
}
