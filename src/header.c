/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 00:03:44 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/12 19:13:16 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
 ** use this to get the last header in memory
*/

uint8_t		*go_to_last_header(uint8_t *header)
{
	uint64_t	tmp;
	uint8_t		*addr;

	addr = header;
	addr += 2;
	tmp = read_size(addr);
	while (tmp != 0)
	{
		addr = (uint8_t *)tmp + 2;
		tmp = read_size(addr);
	}
	return (addr - 2);
}

uint8_t		*go_to_last_header_small(uint8_t *header)
{
	uint64_t	tmp;
	uint8_t		*addr;

	addr = header;
	addr += 4;
	tmp = read_size(addr);
	while (tmp != 0)
	{
		addr = (uint8_t *)tmp + 4;
		tmp = read_size(addr);
	}
	return (addr - 4);
}

/*
 ** use this only for large header
*/

uint8_t		*go_to_last_header_large(uint8_t *header)
{
	uint64_t	tmp;
	uint8_t		*addr;

	addr = header;
	addr += 8;
	tmp = read_size(addr);
	while (tmp != 0)
	{
		addr = (uint8_t *)tmp + 8;
		tmp = read_size(addr);
	}
	return (addr - 8);
}

/*
 ** write new last header addr into the current last header
*/

void		write_next_area_addr(uint64_t next_addr, uint8_t *header)
{
	int			i;
	int			offset;
	uint8_t		*addr;

	i = 0;
	offset = 56;
	addr = go_to_last_header(header) + 2;
	while (i < 8)
	{
		addr[i] = (uint8_t)(next_addr >> offset);
		i++;
		offset -= 8;
	}
}

void		write_next_area_addr_small(uint64_t next_addr, uint8_t *header)
{
	int		i;
	int		offset;
	uint8_t	*addr;

	i = 0;
	offset = 56;
	addr = go_to_last_header_small(header) + 4;
	while (i < 8)
	{
		addr[i] = (uint8_t)(next_addr >> offset);
		i++;
		offset -= 8;
	}
}
