/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_and_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 07:35:56 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/12 06:07:23 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			put_u32inu8(uint8_t *addr, uint32_t size)
{
	int		i;
	int		off;

	i = 0;
	off = 24;
	while (i < 4)
	{
		addr[i] = (uint8_t)(size >> off);
		i++;
		off -= 8;
	}
}

void			put_u16inu8(uint8_t *addr, uint16_t size)
{
	addr[0] = (uint8_t)(size >> 8);
	addr[1] = (uint8_t)(size);
}

uint32_t		read32in8_block(uint8_t *addr)
{
	uint32_t	nu;

	nu = ((uint32_t)((addr)[0] & 0x7f) << 24) | \
		((uint32_t)(addr)[1] << 16) | \
		((uint32_t)(addr)[2] << 8) | \
		((uint32_t)(addr)[3]);
	return (nu);
}

uint32_t		read32in8(uint8_t *addr)
{
	uint32_t	nu;

	nu = ((uint32_t)(addr)[0] << 24) | \
		((uint32_t)(addr)[1] << 16) | \
		((uint32_t)(addr)[2] << 8) | \
		((uint32_t)(addr)[3]);
	return (nu);
}

uint16_t		read16in8_block(uint8_t *addr)
{
	uint16_t	val;

	val = ((uint16_t)((addr[0] & 0x7f) << 8));
	val |= ((uint16_t)addr[1]);
	return (val);
}

uint16_t		read16in8(uint8_t *addr)
{
	uint16_t	val;

	val = ((uint16_t)(addr[0]) << 8);
	val |= ((uint16_t)addr[1]);
	return (val);
}

void			put_size_tiny(uint8_t *ptr, uint8_t size)
{
	*ptr = size;
}

uint64_t		read_size(uint8_t *addr)
{
	uint64_t		nu;

	nu = ((uint64_t)(addr)[0] << 56) | \
		((uint64_t)(addr)[1] << 48) | \
		((uint64_t)(addr)[2] << 40) | \
		((uint64_t)(addr)[3] << 32) | \
		((uint64_t)(addr)[4] << 24) | \
		((uint64_t)(addr)[5] << 16) | \
		((uint64_t)(addr)[6] << 8) | \
		((uint64_t)(addr)[7]);
	return (nu);
}
