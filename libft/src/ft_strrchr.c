/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:44:07 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/24 17:25:24 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				cpt;
	unsigned char	o;
	char			*str;

	o = (unsigned char)c;
	str = (char *)s;
	i = 0;
	cpt = 0;
	while (*s != '\0')
	{
		if (*s == o)
		{
			str = str + i;
			i = 0;
			cpt++;
		}
		s++;
		i++;
	}
	if (o == '\0')
		return (str + i);
	if (cpt > 0)
		return (str);
	return (NULL);
}
