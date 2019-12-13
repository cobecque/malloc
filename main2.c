/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:07:10 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/10 20:04:32 by rostroh          ###   ########.fr       */
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

#define l1 45
#define l2 47
#define l3 52
#define l4 15
#define l5 45
#define l6 50
#define l7 49
#define l8 46
#define l9 50
#define l10 48

void			loop(char *s, int l)
{
	for (int i = 0; i < l; i++)
		s[i] = '0';
}

int				main(void)
{
	char	*s1 = NULL;
	char	*s2 = NULL;
	char	*s3 = NULL;
	char	*s4 = NULL;
	char	*s5 = NULL;
	char	*s6 = NULL;
	char	*s7 = NULL;
	char	*s8 = NULL;
	char	*s9 = NULL;
	char	*s10 = NULL;

	s1 = malloc(l1);
	s2 = malloc(l2);
	s3 = malloc(l3);
	s4 = malloc(l4);
	s5 = malloc(l5);
	s6 = malloc(l6);
	s7 = malloc(l8);
	s8 = malloc(l8);
	s9 = malloc(l9);
	s10 = malloc(l10);
	loop(s1, l1);
	loop(s2, l2);
	loop(s3, l3);
	loop(s4, l4);
	loop(s5, l5);
	loop(s6, l6);
	loop(s7, l7);
	loop(s8, l8);
	loop(s9, l9);
	loop(s10, l10);
}
