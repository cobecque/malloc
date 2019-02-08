/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 23:45:38 by cobecque          #+#    #+#             */
/*   Updated: 2018/11/23 06:29:57 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*curr1;
	unsigned char	*curr2;

	i = 0;
	curr1 = (unsigned char *)src;
	curr2 = (unsigned char *)dst;
	while (i < n)
	{
		*curr2 = *curr1;
		i++;
		curr1++;
		curr2++;
	}
	return (dst);
}
