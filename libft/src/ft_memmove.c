/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:45:29 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:43:45 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void *dest;

	dest = malloc(sizeof(void) * len);
	if (dest != NULL)
	{
		dest = ft_memcpy(dest, src, len);
		dst = ft_memcpy(dst, dest, len);
	}
	free(dest);
	return (dst);
}
