/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 07:15:44 by arabefam          #+#    #+#             */
/*   Updated: 2024/05/24 10:47:57 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = -1;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i++, n-- > 0)
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
	return (dest);
}
