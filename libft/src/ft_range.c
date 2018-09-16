/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 00:10:20 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/30 00:21:07 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int		*tab;
	int		i;

	i = 0;
	if (min >= max)
		return (NULL);
	else
	{
		tab = (int *)malloc(sizeof(int) * (max - min));
		if (!tab)
			return (NULL);
		while (min < max)
		{
			tab[i] = min;
			i++;
			min++;
		}
	}
	return (tab);
}
