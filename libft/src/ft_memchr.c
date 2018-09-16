/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:17:59 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 03:11:49 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*curr;
	unsigned char	o;

	i = 0;
	curr = (unsigned char *)s;
	o = (unsigned char)c;
	while (i < n)
	{
		if (curr[i] == o)
			return (curr + i);
		i++;
	}
	return (NULL);
}
