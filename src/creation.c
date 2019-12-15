/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:59:16 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/15 18:59:17 by cobecque         ###   ########.fr       */
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
