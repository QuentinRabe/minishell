/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:38:52 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/20 14:15:02 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	token_count(char *s, char *set)
{
	int		count;
	short	is_inside;

	count = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && is_in(set, *s, NULL))
			s++;
		is_inside = 0;
		while (*s != '\0' && !is_in(set, *s, NULL))
		{
			if (!is_inside)
				count++;
			is_inside = 1;
			s++;
		}
	}
	return (count);
}

static int	count_len(char *s, char *set)
{
	int		len;
	char	*ptr;

	if (!s || !set)
		return (0);
	ptr = s;
	while (*ptr && !is_in(set, *ptr, NULL))
		ptr++;
	len = ptr - s;
	return (len);
}

static char	**split_helper(t_split split, char *s, char *set)
{
	int	len;

	while (*s != '\0')
	{
		while (*s != '\0' && is_in(set, *s, NULL))
			s++;
		if (*s != '\0')
		{
			len = count_len(s, set);
			split.list[split.i] = ft_substr(s, 0, len);
			if (!split.list[split.i])
			{
				while (split.i >= 0)
					free(split.list[split.i--]);
				free(split.list);
				return (NULL);
			}
			s = s + len;
			split.i++;
		}
	}
	split.list[split.i] = NULL;
	return (split.list);
}

char	**ft_split_set(char *s, char *set)
{
	t_split	split;
	char	**list;

	if (!token_count(s, set))
	{
		list = (char **) malloc(2 * sizeof(char *));
		list[0] = ft_strdup("");
		list[1] = NULL;
		return (list);
	}
	split.list = (char **) malloc((token_count(s, set) + 1) * sizeof(char *));
	if (!split.list)
	{
		free(split.list);
		return (NULL);
	}
	split.i = 0;
	return (split_helper(split, s, set));
}
