/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 04:50:58 by rostroh           #+#    #+#             */
/*   Updated: 2019/08/12 05:00:20 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
 ** create header for large malloc
*/

void		creat_header_large(uint8_t *ptr)
{
	put_u64inu8(ptr, 16);
	put_u64inu8(ptr + 1, 0);
}

/*
 ** create header for small and tiny malloc
*/

void		creat_header(uint16_t *ptr, int off)
{
	*ptr = 10;
	*(ptr + off) = 0;
}
