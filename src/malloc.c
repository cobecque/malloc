/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 22:32:09 by rostroh           #+#    #+#             */
/*   Updated: 2019/09/19 18:22:19 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			print_total(int total)
{
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void				show_alloc_mem(void)
{
	int		total;

	total = 0;
	if (g_all_malloc.tiny != NULL)
	{
		ft_putstr("TINY: 0x");
		ft_puthex((unsigned long)(g_all_malloc.tiny));
		ft_putchar('\n');
		total += print_tiny();
	}
	if (g_all_malloc.small != NULL)
	{
		ft_putstr("SMALL: 0x");
		ft_puthex((unsigned long)(g_all_malloc.small));
		ft_putchar('\n');
		total += print_small();
	}
	if (g_all_malloc.large != NULL)
	{
		ft_putstr("LARGE: 0x");
		ft_puthex((unsigned long)(g_all_malloc.large));
		ft_putchar('\n');
		total += print_large();
	}
	print_total(total);
}

static void			init_global(void)
{
	g_all_malloc.size_page = getpagesize();
	g_all_malloc.tiny_size = SIZE_TINY;
	g_all_malloc.small_size = SIZE_SMALL;
}

void				free(void *ptr)
{
	uint8_t		*addr;

	if (!ptr)
		;
	else
	{
		addr = (uint8_t*)ptr;
		if (is_allocated(addr) == 0)
			;
		else
			clear_area(addr);
	}
}

void				*malloc(size_t size)
{
	void	*ptr;

	if (size % 8 != 0)
		size += 8 - (size % 8);
	if (g_all_malloc.small_size == 0 || g_all_malloc.tiny_size == 0)
		init_global();
	if (size <= g_all_malloc.tiny_size)
		ptr = creat_tiny((uint16_t)size);
	else if (size <= g_all_malloc.small_size)
		ptr = creat_small((uint16_t)size);
	else
		ptr = creat_large((uint64_t)size);
	return (ptr);
}
