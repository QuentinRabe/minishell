/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:26:49 by arabefam          #+#    #+#             */
/*   Updated: 2024/10/21 08:01:07 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	st_strcat(char const *s1, char const *s2, char	*joined)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		joined[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		joined[j] = s2[i];
		j++;
		i++;
	}
	joined[j] = '\0';
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	len;
	char	*joined;

	if (!s1)
	{
		s1 = (char *) malloc(sizeof(char));
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *) malloc((len) * sizeof(char));
	if (!joined)
		return (NULL);
	st_strcat(s1, s2, joined);
	return (joined);
}
