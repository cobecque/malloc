/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:47:32 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/22 23:26:54 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	char			*ptr;
	unsigned int	i;

	if (s)
	{
		new = (char *)malloc(sizeof(char) * len + 1);
		if (new)
		{
			ptr = new;
			i = len + start;
			while (start < i)
			{
				*ptr = s[start];
				ptr++;
				start++;
			}
			*ptr = '\0';
			return (new);
		}
		return (NULL);
	}
	return (NULL);
}
