/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:27:00 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:43:29 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*current;

	i = 0;
	current = (unsigned char *)b;
	while (i < len)
	{
		*current = (unsigned char)c;
		i++;
		current++;
	}
	return (b);
}
