/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 22:32:09 by rostroh           #+#    #+#             */
/*   Updated: 2019/03/09 18:42:41 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t 	mutex;

void		show_alloc_mem(void)
{
	int		total;

	total = 0;
	if (g_all_malloc.tiny != NULL)
	{
		ft_putstr("TINY: 0x");
		ft_puthex((unsigned long)(g_all_malloc.tiny + 11));
		ft_putchar('\n');
		total += print_tiny();
	}
	if (g_all_malloc.small != NULL)
	{
		ft_putstr("SMALL: 0x");
		ft_puthex((unsigned long)(g_all_malloc.small + 12));
		ft_putchar('\n');
		total += print_small();
	}
	if (g_all_malloc.large != NULL)
	{
		ft_putstr("LARGE: 0x");
		ft_puthex((unsigned long)(g_all_malloc.large + 24));
		ft_putchar('\n');
		total += print_large();
	}
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putchar('\n');
	ft_putchar('\n');
}

void		init_global(void)
{
	g_all_malloc.size_page = getpagesize();
	g_all_malloc.tiny_size =\
							(((g_all_malloc.size_page - 24) * 2) - 800) / 100;
	g_all_malloc.small_size =\
							(((g_all_malloc.size_page - 24) * 33) - 800) / 100;
}

void		free(void *ptr)
{
	uint8_t		*addr;

	pthread_mutex_lock(&mutex);
	/*ft_putstr("\nIci free : 0x");
	ft_puthex((unsigned long)ptr);
	ft_putchar('\n');*/
	if (!ptr)
		;
	else
	{
		addr = (uint8_t*)ptr;
		if (is_allocated(addr) == 0)
			;
		else
		{
			clear_area(addr);
		}
	}
	pthread_mutex_unlock(&mutex);
}

void		*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&mutex);
/*	ft_putstr("\nmalloc size = ");
	ft_putnbr(size);
	ft_putchar('\n');
*/	if (size % 8 != 0)
	{
		//ft_putstr("\nchange size : ");
		//ft_putnbr(size);
		size += 8 - (size % 8);
		/*ft_putstr("   en : ");
		ft_putnbr(size);
		ft_putchar('\n');*/
	}
	if (g_all_malloc.small_size == 0 || g_all_malloc.tiny_size == 0)
		init_global();
	if (size < g_all_malloc.tiny_size)
		ptr = creat_tiny((uint8_t)size);
	else if (size < g_all_malloc.small_size)
		ptr = creat_small((uint16_t)size);
	else
		ptr = creat_large((uint64_t)size);
	/*ft_putstr("\nSalut malloc: 0x");
	ft_puthex((unsigned long)(ptr));
	ft_putstr("\n\n");*/
	pthread_mutex_unlock(&mutex);
	return (ptr);
}
