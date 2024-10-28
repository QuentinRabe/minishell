/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:16:41 by arabefam          #+#    #+#             */
/*   Updated: 2024/05/24 13:11:35 by quentin          ###   ########.fr       */
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
