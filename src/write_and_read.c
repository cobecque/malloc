/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_and_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 07:35:56 by cobecque          #+#    #+#             */
/*   Updated: 2019/02/08 07:56:24 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			put_u16inu8(uint8_t *addr, uint16_t size)
{
	addr[0] = (uint8_t)(size >> 8);
	addr[1] = (uint8_t)(size);
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
