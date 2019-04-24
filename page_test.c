/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:11:05 by rostroh           #+#    #+#             */
/*   Updated: 2019/04/18 19:20:10 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>

int				main(void)
{
	void		*adr;

	adr = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (0);
}
