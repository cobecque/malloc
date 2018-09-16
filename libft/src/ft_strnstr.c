/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:33:06 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:28:05 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = i;
		k = 0;
		if (little[k] == '\0')
			return ((char*)big);
		while (big[j] == little[k] && j < len)
		{
			j++;
			k++;
			if (little[k] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
