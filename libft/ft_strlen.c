/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:41:58 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/20 13:45:43 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;
	int		i;

	count = 0;
	i = -1;
	if (!s)
		return (0);
	while (s[++i] != '\0')
		count++;
	return (count);
}
