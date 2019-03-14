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

void		show_alloc_mem(void)
{
	int		total;

	total = 0;
	if (g_all_malloc.tiny != NULL)
	{
		printf("TINY: 0x%lX\n", (unsigned long)g_all_malloc.tiny + 11);
		total += print_tiny();
	}
	if (g_all_malloc.small != NULL)
	{
		printf("SMALL: 0x%lX\n", (unsigned long)g_all_malloc.small + 12);
		total += print_small();
	}
	if (g_all_malloc.large != NULL)
	{
		printf("LARGE: 0x%lX\n", (unsigned long)g_all_malloc.large + 24);
		total += print_large();
	}
	printf("Total: %d octets\n", total);
}

void		init_global(void)
{
	g_all_malloc.size_page = getpagesize();
	g_all_malloc.tiny_size =\
							(((g_all_malloc.size_page - 24) * 2) - 800) / 100;
	g_all_malloc.small_size =\
							(((g_all_malloc.size_page - 24) * 16) - 800) / 100;
	printf("page size = %zu\n", g_all_malloc.size_page);
	printf("tiny size = %zu\n", g_all_malloc.tiny_size);
	printf("small size = %zu\n", g_all_malloc.small_size);
}

void		free(void *ptr)
{
	uint8_t		*addr;

	if (!ptr)
		exit(0);
	addr = (uint8_t*)ptr;
	if (is_allocated(addr) == 0)
		printf("PHILLIPE JE SAIS OU TU TE CACHES !\n");
	else
		clear_area(addr);
}

void		*malloc(size_t size)
{
	void	*ptr;

	puts("Malloc de rostroh");
	if (g_all_malloc.small_size == 0 || g_all_malloc.tiny_size == 0)
		init_global();
	if (size < g_all_malloc.tiny_size)
		ptr = creat_tiny((uint8_t)size);
	else if (size < g_all_malloc.small_size)
		ptr = creat_small((uint16_t)size);
	else
		ptr = creat_large((uint64_t)size);
	return (ptr);
}
