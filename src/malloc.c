/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:59:43 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/15 19:02:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			print_total(int total)
{
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putchar('\n');
}

static void			init_global(void)
{
	g_all_malloc.size_page = getpagesize();
	g_all_malloc.tiny_size = SIZE_TINY;
	g_all_malloc.small_size = SIZE_SMALL;
	g_all_malloc.g_count = 0;
	g_all_malloc.old_count = 0;
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

void				free(void *ptr)
{
	uint8_t		*addr;

	if (!ptr || ptr == 0)
		;
	else
	{
		addr = (uint8_t*)ptr;
		if (is_allocated(addr) == 0)
			;
		else
			clear_area(addr);
		if (VERBOSE == 1 && (g_all_malloc.g_count != g_all_malloc.old_count \
					|| g_all_malloc.old_count == 0))
		{
			g_all_malloc.old_count = g_all_malloc.g_count;
			ft_putstr("count page: ");
			ft_putnbr(g_all_malloc.g_count);
			ft_putchar('\n');
		}
	}
}

void				*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
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
	if (VERBOSE == 1 && (g_all_malloc.g_count != g_all_malloc.old_count \
				|| g_all_malloc.old_count == 0))
	{
		g_all_malloc.old_count = g_all_malloc.g_count;
		ft_putstr("count page: ");
		ft_putnbr(g_all_malloc.g_count);
		ft_putchar('\n');
	}
	return (ptr);
}
