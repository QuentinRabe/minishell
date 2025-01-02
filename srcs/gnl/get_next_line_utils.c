/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:22:48 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 13:59:48 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contain_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_strcat(char *s1, char *s2, char *s)
{
	int	i;
	int	j;

	i = -1;
	if (s1)
	{
		while (s1[++i] != '\0')
			s[i] = s1[i];
	}
	j = 0;
	while (s2[j] != '\0')
		s[i++] = s2[j++];
	s[i] = '\0';
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s;
	int		len;

	if (!s1)
	{
		s1 = (char *) malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	len = ft_strlen_gnl(s1, '\0') + ft_strlen_gnl(s2, '\0');
	s = (char *) malloc((len + 1) * sizeof(char));
	if (!s)
		return (free(s), NULL);
	ft_strcat(s1, s2, s);
	return (free(s1), s);
}

int	ft_strlen_gnl(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != c)
	{
		count++;
		str++;
	}
	return (count);
}

int	get_len(char *store)
{
	int	len;

	if (contain_newline(store))
		len = ft_strlen_gnl(store, '\n') + 1;
	else
		len = ft_strlen_gnl(store, '\0');
	return (len);
}
