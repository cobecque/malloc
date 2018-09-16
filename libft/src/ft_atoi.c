/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:40:36 by cobecque          #+#    #+#             */
/*   Updated: 2017/08/14 01:25:07 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		space(int *n, const char *str)
{
	int i;

	i = 0;
	while (str[i] < 33 && str[i] >= 0)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		*n = *n * -1;
		i++;
	}
	return (i);
}

int				ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	res;

	i = 0;
	n = 1;
	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			res = res * 10 + str[i] - 48;
		}
		else if (str[i] < 33 && str[i] >= 0 && i == 0)
			i = space(&n, str) - 1;
		else if ((str[i] == '-' || str[i] == '+') && i == 0)
		{
			if (str[0] == '-')
				n = -n;
		}
		else if (str[i] < 48 || str[i] > 57)
			return (res * n);
		i++;
	}
	return (res * n);
}
