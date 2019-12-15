/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 09:38:44 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 02:55:48 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				look_addr(uint8_t *look_up, uint8_t *to_find)
{
	int			val;

	look_up += 10;
	if (look_up == to_find)
	{
		if ((*(look_up - 2) & 0x80) == 0x80)
			return (0);
		return (1);
	}
	look_up -= 2;
	val = read16in8_block(look_up);
	while (val != 0)
	{
		look_up += val + 4;
		if (look_up == to_find)
		{
			if ((*(look_up - 2) & 0x80) == 0x80)
				return (0);
			return (1);
		}
		look_up -= 2;
		val = read16in8_block(look_up);
	}
	return (0);
}

static void		get_size_jump(uint16_t *size, uint16_t *jump, uint8_t *current)
{
	*size = 2;
	*jump = 2;
	if (current == g_all_malloc.small)
		*size = 4;
	if (current == g_all_malloc.large)
	{
		*jump = 8;
		*size = -8;
	}
}

static int		free_first_large(uint8_t *addr, uint64_t tmp, int nb)
{
	uint8_t		*current;

	current = NULL;
	if (addr - 16 == g_all_malloc.large)
	{
		current = (uint8_t *)tmp;
		tmp = read_u64inu8(current + 8);
		if (tmp != 0)
			g_all_malloc.large = current;
		else
			g_all_malloc.large = NULL;
	}
	g_all_malloc.g_count -= nb;
	munmap(addr - 16, nb * g_all_malloc.size_page);
	return (0);
}

int				calc_nb_page_large(uint64_t size)
{
	int		nb;

	nb = (size + 16) / g_all_malloc.size_page;
	if ((size + 16) % g_all_malloc.size_page != 0)
		nb++;
	return (nb);
}

int				free_large(uint8_t *addr, uint8_t *current)
{
	uint64_t		tmp;
	uint8_t			*old;
	int				nb;

	tmp = read_u64inu8(current + 8);
	nb = calc_nb_page_large(read_u64inu8(current));
	if (current == addr - 16)
		return (free_first_large(addr, tmp, nb));
	old = current;
	while (tmp != 0)
	{
		current = (uint8_t *)tmp;
		tmp = read_u64inu8(current + 8);
		nb = calc_nb_page_large(read_u64inu8(current));
		if (current == addr - 16)
		{
			if (old != NULL)
				put_u64inu8(old + 8, read_u64inu8(current + 8));
			g_all_malloc.g_count -= nb;
			munmap(addr - 16, nb * g_all_malloc.size_page);
			return (0);
		}
		old = current;
	}
	return (0);
}

int				is_allocated(uint8_t *addr)
{
	uint64_t		tmp;
	uint8_t			*current;
	uint16_t		size;
	uint16_t		jump;

	current = check_type_of_malloc(addr);
	if (current == 0)
		return (0);
	get_size_jump(&size, &jump, current);
	if (jump == 8)
		return (free_large(addr, current));
	current += size;
	tmp = read_size(current);
	while (tmp != 0)
	{
		if ((uint64_t)current < (uint64_t)addr && (uint64_t)addr < tmp)
			return (look_addr(current, addr));
		current = (uint8_t *)tmp + size;
		tmp = read_size(current);
	}
	return (look_addr(current, addr));
}
