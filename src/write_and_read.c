/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_and_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 07:35:56 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/13 03:11:01 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			put_u32inu8(uint8_t *addr, uint32_t size)
{
	int		i;
	int		off;

	i = 0;
	off = 24;
	while (i < 4)
	{
		addr[i] = (uint8_t)(size >> off);
		i++;
		off -= 8;
	}
}

void			put_u16inu8(uint8_t *addr, uint16_t size)
{
	addr[0] = (uint8_t)(size >> 8);
	addr[1] = (uint8_t)(size);
}

void			put_size_tiny(uint8_t *ptr, uint8_t size)
{
	*ptr = size;
}
