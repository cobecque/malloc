/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 01:36:51 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 19:14:34 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;
	t_list	*lst;

	lst = *alst;
	while (lst != NULL)
	{
		ptr = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = ptr;
	}
	*alst = NULL;
}
