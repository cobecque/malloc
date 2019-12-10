/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:07:10 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/10 19:36:16 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "includes/malloc.h"
//#include <stdlib.h>

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(const char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void			ft_putnbr(int n)
{
	if (n < 0)
	{
		puts("-");
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else 
		ft_putchar(n + '0');
}

int				main(void)
{
	char	*str = NULL;

	for (int i = 1; i < 4096; i++)
	{
		ft_putstr("Salut\n");
		str = malloc(i);
		show_alloc_mem();
	//	if (str)
	//	{
			for (int j = 0; j < i; j++)
				str[j] = j;
	//	}
		free(str);
		show_alloc_mem();
		ft_putstr("i = ");
		ft_putnbr(i);
		ft_putstr("   --> fini\n\n\n");
	}
}
