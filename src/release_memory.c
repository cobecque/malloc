/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:04:19 by cobecque          #+#    #+#             */
/*   Updated: 2019/02/08 09:21:44 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free_area_small(uint8_t *addr)
{
	uint8_t		*tmp;
	uint8_t		*free_this;
	uint64_t	before;
	uint64_t	next;
	int			first;

	tmp = addr + 2;
	next = read_size(tmp);
	before = (uint64_t)tmp;
	first = 0;
	while (next != 0 || first == 0)
	{
		if (read16in8(tmp - 2) - 10 == 0)
		{
			free_this = tmp;
			tmp = (uint8_t *)before;
			put_u16inu8(tmp, (uint16_t)(*free_this));
			munmap(free_this, g_all_malloc.size_page * 16);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 2;
		next = read_size(tmp);
	}
}

void		free_area_tiny(uint8_t *addr)
{
	uint8_t		*tmp;
	uint8_t		*free_this;
	uint64_t	before;
	uint64_t	next;
	int			first;

	tmp = addr + 2;
	next = read_size(tmp);
	before = (uint64_t)tmp;
	first = 0;
	while (next != 0 || first == 0)
	{
		if (read16in8(tmp - 2) - 10 == 0)
		{
			free_this = tmp;
			tmp = (uint8_t *)before;
			put_u16inu8(tmp, (uint16_t)(*free_this));
			munmap(free_this, g_all_malloc.size_page * 2);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 2;
		next = read_size(tmp);
	}
}

void		free_area_large(uint8_t *header, uint8_t *addr)
{
	uint8_t		*tmp;
	uint8_t		*free_this;
	uint64_t	before;
	uint64_t	next;
	uint64_t	size;

	tmp = header + 8;
	next = read_size(tmp);
	size = read_u64inu8(tmp - 8);
	before = (uint64_t)tmp;
	while (next != 0 || size != 0)
	{
		size = read_u64inu8(tmp - 8);
		if (read_u64inu8(tmp - 8) - 16 == 0 && tmp - 8 == addr - 24)
		{
			free_this = tmp;
			tmp = (uint8_t *)before;
			put_u64inu8(tmp, (uint64_t)(*free_this));
			munmap(free_this, size);
		}
		if (next == 0)
			break ;
		before = (uint64_t)tmp;
		tmp = (uint8_t *)next + 8;
		next = read_size(tmp);
	}
}
