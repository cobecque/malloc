/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:50:39 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/24 17:47:36 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (big[i] != '\0')
	{
		j = i;
		k = 0;
		while (big[j] == little[k] && little[k])
		{
			j++;
			k++;
		}
		if (little[k] == '\0')
			return ((char *)big + i);
		i++;
	}
	if (!*big && !*little)
		return ((char *)big);
	return (NULL);
}
