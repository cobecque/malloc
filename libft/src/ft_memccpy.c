/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:30:59 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:44:45 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*curr1;
	unsigned char	*curr2;
	unsigned char	o;

	i = 0;
	curr1 = (unsigned char *)src;
	curr2 = (unsigned char *)dst;
	o = (unsigned char)c;
	while (i < n)
	{
		if (*curr1 == o)
		{
			*curr2 = *curr1;
			return (curr2 + 1);
		}
		*curr2 = *curr1;
		i++;
		curr1++;
		curr2++;
	}
	return (NULL);
}
