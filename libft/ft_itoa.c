/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:07:13 by arabefam          #+#    #+#             */
/*   Updated: 2024/05/24 10:47:04 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_rev_tab(char *tab, int size)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		i++;
		j--;
	}
	return (tab);
}

static void	itoa_hlp(long	*nbr, int *i, char	*str, int n)
{
	while (*nbr > 0)
	{
		str[*i] = (*nbr % 10) + '0';
		*i = *i + 1;
		*nbr /= 10;
	}
	if (n < 0)
	{
		str[*i] = '-';
		*i = *i + 1;
	}
	str[*i] = '\0';
	ft_rev_tab(str, count_digit(n));
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = (long) n;
	str = (char *) malloc((count_digit(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (nbr == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (!str)
		return (NULL);
	i = 0;
	if (nbr < 0)
		nbr = nbr * (-1);
	itoa_hlp(&nbr, &i, str, n);
	return (str);
}
