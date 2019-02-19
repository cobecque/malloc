/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:44:09 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/19 01:06:10 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			is_tiny_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint16_t	size;
	uint64_t	tmp;

	if (*(addr - 1) == 0)
		return (-1);
	header = g_all_malloc.tiny;
	if (header == 0)
		return (-1);
	size = read16in8(header);
	tmp = read_size(header + 2);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + g_all_malloc.size_page * 2)
			return (1);
		header = (uint8_t *)tmp;
		tmp = read_size(header + 2);
	}
	if (addr >= header && addr <= header + g_all_malloc.size_page * 2)
		return (1);
	return (0);
}

int			is_small_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint16_t	size;
	uint64_t	tmp;

	if (read16in8_block(addr - 2) == 0)
		return (-1);
	header = g_all_malloc.small;
	if (header == NULL)
		return (-1);
	size = read16in8(header);
	tmp = read_size(header + 2);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + g_all_malloc.size_page * 16)
			return (1);
		header = (uint8_t *)tmp;
		tmp = read_size(header + 2);
	}
	if (addr >= header && addr <= header + g_all_malloc.size_page * 16)
		return (1);
	return (0);
}

int			is_large_malloc(uint8_t *addr)
{
	uint8_t		*header;
	uint64_t	size;
	uint64_t	tmp;

	if (read_u64inu8(addr - 8) == 0)
		return (-1);
	header = g_all_malloc.large;
	if (header == 0)
		return (-1);
	size = read_u64inu8(header);
	tmp = read_u64inu8(header + 8);
	while (tmp != 0)
	{
		if (addr >= header && addr <= header + size)
			return (1);
		header = (uint8_t *)tmp;
		tmp = read_u64inu8(header + 8);
	}
	if (addr >= header && addr <= header + size)
		return (1);
	return (0);
}

uint8_t		*check_type_of_malloc(uint8_t *addr)
{
	if (is_tiny_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.tiny);
	else if (is_small_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.small);
	else if (is_large_malloc(addr) == 1)
		return ((uint8_t *)g_all_malloc.large);
	else if (is_large_malloc(addr) == -1 && is_tiny_malloc(addr) == -1 \
			&& is_small_malloc(addr) == -1)
		return (NULL);
	return (NULL);
}
