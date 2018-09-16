/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:37:51 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:42:24 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	o;
	char			*str;

	i = 0;
	o = (unsigned char)c;
	str = (char *)s;
	while (s[i] != '\0')
	{
		if (s[i] == o)
			return (str + i);
		i++;
	}
	if (o == '\0')
		return (str + i);
	return (NULL);
}
