/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 03:06:54 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/05 18:02:17 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
