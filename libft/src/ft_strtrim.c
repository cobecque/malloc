/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:05:50 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:32:57 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_emptystring(void)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * 1 + 1);
	if (new == NULL)
		return (NULL);
	*new = '\0';
	return (new);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		size;
	int		k;
	char	*new;

	i = 0;
	k = 0;
	if (s)
	{
		size = ft_strlen(s);
		while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
			i++;
		if (s[i] == '\0')
			return (ft_emptystring());
		while (s[size - 1] == ' ' || s[size - 1] == '\n' || s[size - 1] == '\t')
			size--;
		new = (char *)malloc(sizeof(char) * (size - i + 1));
		if (new == NULL)
			return (NULL);
		while (i < size)
			new[k++] = s[i++];
		new[k] = '\0';
		return (new);
	}
	return (NULL);
}
