/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:37:41 by arabefam          #+#    #+#             */
/*   Updated: 2024/02/24 07:30:50 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*memory;

	memory = (char *) malloc(nmemb * size);
	if (!memory)
		return (NULL);
	ft_bzero(memory, (nmemb * size));
	return ((void *) memory);
}
