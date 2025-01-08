/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 07:15:44 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 11:53:27 by arabefam         ###   ########.fr       */
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
