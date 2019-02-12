/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:40:21 by cobecque          #+#    #+#             */
/*   Updated: 2019/02/12 14:40:23 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int         check_type_size(size_t size, uint16_t s)
{
    if (s == 1 && size < g_all_malloc.tiny_size)
        return (1);
    else if (s == 2 && size < g_all_malloc.small_size && size >= g_all_malloc.tiny_size)
        return (1);
    else if (s == 8 && size >= g_all_malloc.small_size)
        return (1);
    else
        return (-1);
}

void        *add_new_malloc(uint8_t *addr, size_t size)
{
    void    *ret;
    uint8_t *new;

    ret = malloc(size);
    ret = ft_memcpy(ret, addr, size);
    free(addr);
    return (ret);
}

void        *realloc(void *ptr, size_t size)
{
    uint8_t     *header;
    uint8_t     *t;
    uint16_t    s;
    uint64_t    tmp;
    uint16_t    val;
    int         nb_page;

    if (ptr == NULL)
        return (malloc(size));

    t = (uint8_t *)ptr;
    header = check_type_of_malloc(ptr);

    if (header == g_all_malloc.tiny)
        s = 1;
    else if (header == g_all_malloc.small)
        s = 2;
    else
        s = 8;

    if (check_type_size(size, s) == -1)
        return (add_new_malloc((uint8_t *)ptr, size));

    val = val_for_addr(t - s, s);
    tmp = (uint64_t)(t + val);
    t = (uint8_t *)tmp;

    nb_page = 2;
    if (s == 2)
        nb_page = 16;

    if (s == 8)
        return (add_new_malloc((uint8_t *)ptr, size));
    if (val_for_addr((uint8_t *)t, s) == 0 && (uint64_t)(ptr - s + size) < (uint64_t)(g_all_malloc.size_page * nb_page + header))
        return (ptr);
    else
        return(add_new_malloc((uint8_t *)ptr, size));
    return (NULL);
}