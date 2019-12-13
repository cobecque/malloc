/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 22:32:09 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/13 18:01:32 by cobecque         ###   ########.fr       */
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

	if (!ptr || ptr == 0)
		;
	else
	{
		ft_putstr("ici pour un free: ");
		ft_puthex((unsigned long)ptr);
		ft_putchar('\n');
		addr = (uint8_t*)ptr;
		if (is_allocated(addr) == 0)
			ft_putstr("		Pas trouve\n");
		else
			clear_area(addr);
		ft_putstr("Fin free\n");
	}
}

/*void				*test_nul(unsigned char *ptr, int size)
{
	for (int i = 0; i < size; i++)
	{
		ptr[i] = 0;
	}
	return (ptr);
}*/

void				*malloc(size_t size)
{
	void	*ptr;
//	char	*tmp;

	ft_putstr("\nmalloc size :");
	ft_putnbr(size);
	ft_putstr("\n");
	if (size == 0)
	{
		//ft_putstr("RIEN, NUL\n");
		return (NULL);
	}
	if (size % 8 != 0)
		size += 8 - (size % 8);
	//ft_putnbr(size);
	//ft_putchar('\n');
	if (g_all_malloc.small_size == 0 || g_all_malloc.tiny_size == 0)
		init_global();
	if (size <= g_all_malloc.tiny_size)
	{
	//	ft_putstr("normal\n");
		ptr = creat_tiny((uint16_t)size);
	}
	else if (size <= g_all_malloc.small_size)
		ptr = creat_small((uint16_t)size);
	else
		ptr = creat_large((uint64_t)size);
//	ptr = test_nul((unsigned char *)ptr, size);
/*	ft_putstr("Addr return : ");
	ft_puthex((unsigned long)ptr);
	ft_putstr(" Pour faire le beau: ");
	tmp = (char *)ptr;
	ft_putnbr(tmp[size - 1]);
	ft_putstr("\n\n");*/
	//show_alloc_mem();
	ft_putstr("fin malloc\n");
	return (ptr);
}
