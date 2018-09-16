/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:10:51 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/25 14:41:18 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void			*new;

	new = (void *)malloc(sizeof(void) * size);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
