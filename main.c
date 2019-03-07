/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 23:09:50 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/19 00:56:42 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"

int			main(void)
{
    int     i;
    char    *random;
    char    *ptr;
    char    *ptr2;
    char    *ptr3;
    char    *ptr4;
    char    *ptrCrash;

    i = 0;
    //printf("%llu %llu %llu\n", sizeof(size_t), sizeof(void *), sizeof(char));
    /*while (i < 250)
    {
        //printf("lj hifhe;oiheiohio hfo;hf;oie whoihewoi ;hefoihe wiohfiowhio heifoh %d\n", i);
        printf("%d\n", i);
        random = (char *)malloc(sizeof(char) * 4000);
        i++;
    }*/
    //free(random);
    ptr = (char *)malloc(sizeof(char) * 40);
    ptr2 = (char *)malloc(sizeof(char) * 40);
    ptr3 = (char *)malloc(sizeof(char) * 40);
    ptr4 = (char *)malloc(sizeof(char) * 40);
    //ptrCrash = realloc(ptr, 400);
    //ptr = (char *)malloc(sizeof(char) * 400);

    printf("\n\n");
    show_alloc_mem();
    printf("\n\n");
    free(ptr2);
    free(ptr);
    //free(ptr);
    printf("\n\n");
    show_alloc_mem();
    printf("\n\n");
    ptr = (char *)malloc(sizeof(char) * 600);
    printf("\n\n");
    show_alloc_mem();
    printf("\n\n");
    free(ptr3);
    free(ptr4);
    printf("ca passe\n");
    free(ptrCrash);
//    ptrCrash = (char *)malloc(sizeof(char) * 5);
/*    i = 0;
    while (i < 15)
    {
     //   ptrCrash[i] = 'b';
        ptr[i] = 'a';
        i++;
    }
    //ptrCrash[4] = '\0';
    ptr[24] = '\0';*/
    /*ft_putendl(ptr);
    
    //ft_putstr(ptrCrash);*/
    
	return (0);
}
