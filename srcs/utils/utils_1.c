/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:30:34 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 11:47:16 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_in(char *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (true);
		set++;
	}
	return (false);
}

void	trim(char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	free(*str);
	*str = ft_strtrim(tmp, SPACES);
	free(tmp);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
