/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:05:39 by arabefam          #+#    #+#             */
/*   Updated: 2024/05/24 10:47:32 by quentin          ###   ########.fr       */
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
