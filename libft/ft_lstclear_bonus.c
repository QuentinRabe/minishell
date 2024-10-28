/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:41:04 by arabefam          #+#    #+#             */
/*   Updated: 2024/02/26 13:34:51 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	**ptr;
	t_list	*ptmp;

	ptr = lst;
	while (*lst != NULL)
	{
		ptmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ptmp;
	}
	*ptr = NULL;
}
