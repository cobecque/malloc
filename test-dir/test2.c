/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:55:43 by rostroh           #+#    #+#             */
/*   Updated: 2019/08/12 04:03:00 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			main()
{
	int		i;
	char	*adr;

	i = 0;
	while (i < 1024)
	{
		adr = (char *)malloc(1024);
		adr[0] = 42;
		free(adr);
		i++;
	}
	return (0);
}