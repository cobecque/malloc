/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 03:22:59 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/15 02:34:49 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static char	cal_hex(int reste)
{
	if (reste < 10)
		return (reste + '0');
	else
		return (reste - 10 + 'A');
}

void		ft_puthex(uint64_t nb)
{
	char	buf[25];
	char	tmp[25];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (nb == 0)
		ft_putchar('0');
	while (nb > 0)
	{
		buf[i] = cal_hex(nb % 16);
		nb = nb / 16;
		i++;
	}
	i--;
	while (i >= 0)
	{
		tmp[j] = buf[i];
		ft_putchar(tmp[j]);
		i--;
		j++;
	}
	tmp[j] = '\0';
}

int			print_block_tiny(uint8_t *addr, uint16_t size)
{
	uint8_t		*end;

	if ((*addr & 0x80) == 0x80)
		return (0);
	end = addr + size;
	ft_putstr("0x");
	ft_puthex((unsigned long)(addr + 2));
	ft_putstr(" - 0X");
	ft_puthex((unsigned long)(end + 2));
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
	return (size);
}

int			print_block_small(uint8_t *addr, uint16_t size)
{
	uint8_t		*end;

	if ((*addr & 0x80) == 0x80)
		return (0);
	end = addr + size;
	ft_putstr("0x");
	ft_puthex((unsigned long)(addr + 2));
	ft_putstr(" - 0X");
	ft_puthex((unsigned long)(end + 2));
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
	return (size);
}

int			check_type_size(size_t size, uint16_t s)
{
	if (s == 1 && size < g_all_malloc.tiny_size)
		return (1);
	else if (s == 2 && size < g_all_malloc.small_size && size >= \
			g_all_malloc.tiny_size)
		return (1);
	else if (s == 8 && size >= g_all_malloc.small_size)
		return (1);
	else
		return (-1);
}
