/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 22:42:44 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:32:08 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		isnegativ(int *n, int *neg)
{
	if (*n < 0)
	{
		*n = *n * -1;
		*neg = 1;
	}
}

char			*ft_itoa(int n)
{
	int		tmp;
	int		len;
	int		neg;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmp = n;
	len = 2;
	neg = 0;
	isnegativ(&n, &neg);
	while (tmp /= 10)
		len++;
	len = len + neg;
	if ((res = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	res[--len] = '\0';
	while (len--)
	{
		res[len] = n % 10 + 48;
		n = n / 10;
	}
	if (neg == 1)
		res[0] = '-';
	return (res);
}
