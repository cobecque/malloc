/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:01:21 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/15 19:10:10 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "ft_printf.h"
# include "sys/mman.h"

# define VERBOSE 0
# define SIZE_HEADER 10
# define SIZE_HEADER_SMALL 12

# define SIZE_TINY 512
# define SIZE_SMALL 1025

# define NBPAGE_TINY 13
# define NBPAGE_SMALL 51

# define SIZE_MAX_UINT16 0x7FFF

typedef struct		s_malloc
{
	size_t			size_page;
	size_t			tiny_size;
	size_t			small_size;
	void			*tiny;
	void			*small;
	void			*large;
	int				g_count;
	int				old_count;
}					t_malloc;

t_malloc			g_all_malloc;

/*
** block.c
*/

void				ft_puthex(uint64_t nb);
int					print_block_small(uint8_t *addr, uint16_t size);
int					print_block_tiny(uint8_t *addr, uint16_t size);
int					check_type_size(size_t size, uint16_t s);

/*
** check_memory.c
*/

int					free_large(uint8_t *addr, uint8_t *current);
int					look_addr(uint8_t *look_up, uint8_t *to_find);
int					is_allocated(uint8_t *addr);

/*
** clear_area.c
*/

uint8_t				*delet_mem(uint8_t *addr, uint64_t bef, int val, int nb);
uint8_t				*get_next(uint8_t *tmp, uint8_t *addr, int type);
void				clear_area(uint8_t *addr);
/*
** creation.c
*/

void				creat_header_large(uint8_t *ptr);

/*
** get_size.c
*/

uint64_t			val_for_addr_new(uint8_t *look_up, int jump_next);
uint16_t			get_size_type(void *ptr, uint8_t **header);
int					calc_nb_page_large(uint64_t size);
/*
** header.c
*/

uint8_t				*go_to_last_header_large(uint8_t *header);
uint8_t				*go_to_last_header_small(uint8_t *header);
uint8_t				*go_to_last_header(uint8_t *header);
void				write_next_area_addr_small(uint64_t next_addr, uint8_t *h);
void				write_next_area_addr(uint64_t next_addr, uint8_t *header);

/*
** large.c
*/

uint64_t			read_u64inu8(uint8_t *addr);
void				put_u64inu8(uint8_t *addr, uint64_t size);
void				*creat_large(uint64_t size);

/*
** malloc.c
*/

void				*malloc(size_t size);
void				show_alloc_mem(void);
void				free(void *ptr);

/*
** read.c
*/

uint64_t			read_size(uint8_t *addr);
uint32_t			read32in8_block(uint8_t *addr);
uint32_t			read32in8(uint8_t *addr);
uint16_t			read16in8_block(uint8_t *addr);
uint16_t			read16in8(uint8_t *addr);

/*
** realloc.c
*/

void				*realloc(void *ptr, size_t size);

/*
** release_memory.c
*/

void				free_area_small(uint8_t *addr);
void				free_area_tiny(uint8_t *addr);

/*
** show.c
*/

int					print_tiny(void);
int					print_small(void);
int					print_large(void);

/*
** small.c
*/

void				*creat_small(uint16_t size);

/*
** tiny.c
*/

void				*creat_tiny(uint16_t size);

/*
** type.c
*/

uint8_t				*check_type_of_malloc(uint8_t *addr);
int					is_tiny_malloc(uint8_t *addr);
int					is_small_malloc(uint8_t *addr);
int					is_large_malloc(uint8_t *addr);

/*
** write.c
*/

void				put_u16inu8(uint8_t *addr, uint16_t size);
void				put_u32inu8(uint8_t *addr, uint32_t size);

#endif
