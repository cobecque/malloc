/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:55:43 by rostroh           #+#    #+#             */
/*   Updated: 2019/08/25 00:48:38 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int			main()
{
	int		i;
	char	*adr;

	i = 0;
	ft_putstr("lol\n");
	adr = (char *)malloc(400);
	realloc(adr, 410);
	return (0);
}
