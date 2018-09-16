/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:32:05 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:28:41 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	i = 0;
	if (s)
	{
		new = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (new)
		{
			while (s[i] != '\0')
			{
				new[i] = (*f)(i, s[i]);
				i++;
			}
			new[i] = '\0';
			return (new);
		}
		return (NULL);
	}
	return (NULL);
}
