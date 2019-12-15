/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 02:49:46 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 02:59:19 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
 ** Write in a uint64_t in a uint8_t *
*/

void			put_u64inu8(uint8_t *addr, uint64_t size)
{
	int	i;
	int	off;

	i = 0;
	off = 56;
	while (i < 8)
	{
		addr[i] = (uint8_t)(size >> off);
		i++;
		off -= 8;
	}
}

/*
 ** Read a value in uint64_t into a uint8_t *
*/

uint64_t		read_u64inu8(uint8_t *addr)
{
	uint64_t	val;

	val = ((uint64_t)(addr)[0] << 56) |
		((uint64_t)(addr)[1] << 48) |
		((uint64_t)(addr)[2] << 40) |
		((uint64_t)(addr)[3] << 32) |
		((uint64_t)(addr)[4] << 24) |
		((uint64_t)(addr)[5] << 16) |
		((uint64_t)(addr)[6] << 8) |
		((uint64_t)(addr)[7]);
	return (val);
}

/*
 ** Write the new next header addr into the last header create
*/

static void		write_next_addr_large(uint64_t next_addr, uint8_t *header)
{
	int			i;
	int			offset;
	uint8_t		*addr;

	i = 0;
	offset = 56;
	addr = go_to_last_header_large(header) + 8;
	while (i < 8)
	{
		addr[i] = (uint8_t)(next_addr >> offset);
		i++;
		offset -= 8;
	}
}

void			*map_large(uint64_t size)
{
	int		nb_page;

	nb_page = (size + 16) / g_all_malloc.size_page;
	if ((size + 16) % g_all_malloc.size_page != 0)
		nb_page++;
	g_all_malloc.g_count += nb_page;
	return (mmap(0, nb_page * g_all_malloc.size_page, PROT_READ | PROT_WRITE, \
				MAP_ANON | MAP_PRIVATE, -1, 0));
}

/*
 ** Create large malloc
*/

void			*creat_large(uint64_t size)
{
	uint8_t		*area;

	if (g_all_malloc.large == NULL)
	{
		g_all_malloc.large = map_large(size);
		area = g_all_malloc.large;
		if (area == MAP_FAILED)
			return (NULL);
		creat_header_large((uint8_t *)area);
		put_u64inu8(area, size);
		put_u64inu8(area + 8, 0);
		area += 16;
	}
	else
	{
		area = map_large(size);
		write_next_addr_large((uint64_t)area, (uint8_t *)g_all_malloc.large);
		creat_header_large((uint8_t *)area);
		put_u64inu8(area, size);
		put_u64inu8(area + 8, 0);
		area += 16;
	}
	return (area);
}
