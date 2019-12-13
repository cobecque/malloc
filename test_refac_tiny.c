/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_refac_tiny.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:08:27 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/11 16:11:29 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/malloc.h"
#include "./includes/libft.h"

int			main(void)
{
	char		*s1;
	char		*s2;
	char		*s3;
	char		*s4;
	char		*s5;

	s1 = (char *)malloc(sizeof(char) * 16);
	s2 = (char *)malloc(sizeof(char) * 67);
	s3 = (char *)malloc(sizeof(char) * 400);
	s4 = (char *)malloc(sizeof(char) * 124);
	free(s2);
	s5 = (char *)malloc(sizeof(char) * 80);
	return (0);
}
