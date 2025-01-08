/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:16:41 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 11:52:24 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	char			*ptr;
	long			sign;
	unsigned long	nbr;

	sign = 1;
	nbr = 0;
	ptr = (char *) nptr;
	while (*ptr != '\0' && ((*ptr >= '\t' && *ptr <= '\r') || *ptr == ' '))
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	while (*ptr != '\0' && ft_isdigit(*ptr))
	{
		nbr *= 10;
		nbr += (*ptr - '0');
		ptr++;
	}
	return ((long)(sign * nbr));
}
