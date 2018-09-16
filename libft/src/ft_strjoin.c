/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:59:13 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 01:01:15 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count(const char *s1, const char *s2)
{
	return (ft_strlen(s1) + ft_strlen(s2));
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*ptr;

	if (s1 && s2)
	{
		if ((new = (char *)malloc(sizeof(char) * count(s1, s2) + 1)) != NULL)
		{
			ptr = new;
			while (*s1 != '\0')
			{
				*new = *s1;
				s1++;
				new++;
			}
			while (*s2 != '\0')
			{
				*new = *s2;
				s2++;
				new++;
			}
			*new = '\0';
			return (ptr);
		}
	}
	return (NULL);
}
