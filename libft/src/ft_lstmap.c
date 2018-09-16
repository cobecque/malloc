/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 01:46:26 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 20:57:07 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if ((lst)->next == NULL)
		return (ft_memcpy((t_list *)malloc(sizeof(t_list)), f(lst), \
					sizeof(t_list)));
	else
	{
		new = ft_memcpy((t_list *)malloc(sizeof(t_list)), f(lst), \
				sizeof(t_list));
		new->next = ft_lstmap(lst->next, f);
		return (new);
	}
}
