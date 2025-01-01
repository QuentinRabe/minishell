/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:17:35 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/01 10:47:29 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimed;
	size_t		start;
	size_t		end;
	size_t		i;

	start = 0;
	while (s1[start] != '\0' && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_in_set(s1[end - 1], set))
		end--;
	trimed = (char *) malloc(sizeof(char) * (end - start + 1));
	if (!trimed)
		return (NULL);
	i = 0;
	while (start < end)
		trimed[i++] = s1[start++];
	trimed[i] = '\0';
	return (trimed);
}
