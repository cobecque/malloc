/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:31:43 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/25 15:43:01 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	char	*ptr;

	new = (char *)malloc(sizeof(char) * size + 1);
	if (new == NULL)
		return (NULL);
	ptr = new;
	while (size-- > 0)
	{
		*new = '\0';
		new++;
	}
	*new = '\0';
	return (ptr);
}
