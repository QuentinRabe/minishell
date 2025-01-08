/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:36:30 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 11:55:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_set(char *str, char set)
{
	size_t	count;

	count = 0;
	while (*str && *str != set)
	{
		str++;
		count++;
	}
	return (count);
}
