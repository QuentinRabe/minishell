/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:52 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 11:54:31 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*mapnew;

	first = NULL;
	while (lst)
	{
		mapnew = ft_lstnew((*f)(lst->content));
		if (!mapnew)
		{
			while (first)
			{
				mapnew = first->next;
				(*del)(first->content);
				free(first);
				first = mapnew;
			}
			return (NULL);
		}
		ft_lstadd_back(&first, mapnew);
		lst = lst->next;
	}
	return (first);
}
