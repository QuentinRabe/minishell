/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:31:51 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/03 15:08:54 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_in_dq(char *token, int i)
{
	return (is_in_quotes(token, i, '"'));
}

bool	is_in_sq(char *token, int i)
{
	return (is_in_quotes(token, i, '\''));
}

bool	is_in(char *set, char c, int *index)
{
	int	i;

	i = -1;
	if (!set)
		return (false);
	while (set[++i])
	{
		if (c == set[i])
		{
			if (index)
				*index = i;
			return (true);
		}
	}
	return (false);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_msh	*get_msh(int i, t_msh *msh)
{
	static t_msh	*ptr = NULL;

	if (i == 0)
		ptr = msh;
	return (ptr);
}
