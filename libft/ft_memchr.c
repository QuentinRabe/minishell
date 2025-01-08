/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:05:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 11:53:21 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*string;

	if (c == 0 && n == 0)
		return (NULL);
	i = 0;
	string = (void *) s;
	while (i < n)
	{
		if (string[i] == (char) c)
			return (&string[i]);
		i++;
	}
	return (NULL);
}
