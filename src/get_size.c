/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:48:10 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/15 02:58:19 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

uint64_t			val_for_addr_new(uint8_t *look_up, int jump_next)
{
	uint64_t	val;

	if (jump_next != 8)
		val = read16in8_block(look_up);
	if (jump_next == 8)
		val = read_u64inu8(look_up);
	return (val);
}

static uint16_t		return_good_header(void *ptr, uint8_t **header, uint16_t s)
{
	if (*header == g_all_malloc.small)
		*header = get_next(*header + 4, ptr, 4);
	else if (*header == g_all_malloc.tiny)
		*header = get_next(*header + 2, ptr, 2);
	return (s);
}

uint16_t			get_size_type(void *ptr, uint8_t **header)
{
	uint16_t	s;
	uint64_t	next;

	*header = check_type_of_malloc(ptr);
	if (*header == NULL)
		return (0);
	s = 2;
	if (*header == g_all_malloc.small)
		s = 3;
	if (*header == g_all_malloc.large)
	{
		*header += 8;
		next = read_size(*header);
		while (next != 0)
		{
			if ((uint8_t *)ptr >= *header - 8 && (uint8_t *)ptr <= *header -\
					8 + read_u64inu8(*header - 8))
				break ;
			*header = (uint8_t *)next + 8;
			next = read_size(*header);
		}
		*header -= 8;
		s = 8;
	}
	return (return_good_header(ptr, header, s));
}
