/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 22:49:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/19 01:00:03 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "ft_printf.h"
# include "sys/mman.h"
# include <pthread.h>
# define SIZE_HEADER 10

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

typedef struct		s_malloc
{
	size_t			size_page;
	size_t			tiny_size;
	size_t			small_size;
	void			*tiny;
	void			*small;
	void			*large;
}					t_malloc;

t_malloc			g_all_malloc;
extern pthread_mutex_t		mutex;

uint64_t			read_size(uint8_t *addr);
uint64_t			read_u64inu8(uint8_t *addr);

uint16_t			val_for_addr(uint8_t *look_up, int jump_next);
uint16_t			read16in8(uint8_t *addr);
uint16_t			read16in8_block(uint8_t *addr);

uint8_t				*go_to_last_header_large(uint8_t *header);
uint8_t				*go_to_last_header(uint8_t *header);
uint8_t				*check_type_of_malloc(uint8_t *addr);

void				*creat_small(uint16_t size);
void				*creat_large(uint64_t size);
void				*creat_tiny(uint8_t size);

void				write_next_area_addr(uint64_t next_addr, uint8_t *header);
void				put_u16inu8(uint8_t *addr, uint16_t size);
void				put_size_tiny(uint8_t *ptr, uint8_t size);
void				put_u64inu8(uint8_t *addr, uint64_t size);
void				creat_header_large(uint8_t *ptr);
void				creat_header(uint16_t *ptr);

void				free_area_large(uint8_t *header, uint8_t *addr);
void				free_area_small(uint8_t *addr);
void				free_area_tiny(uint8_t *addr);

void				ft_puthex(unsigned long nb);

int					is_tiny_malloc(uint8_t *addr);
int					is_small_malloc(uint8_t *addr);
int					is_large_malloc(uint8_t *addr);
int					look_addr(uint8_t *look_up, uint8_t *to_find, uint16_t s);
int					is_allocated(uint8_t *addr);
int					print_tiny(void);
int					print_small(void);
int					print_large(void);

void				show_alloc_mem(void);
void				clear_area(uint8_t *addr);

#endif
