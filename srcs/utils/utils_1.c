/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:30:34 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 20:18:19 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_list(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr)
	{
		printf("[%s][%d]\n", ptr->value, ptr->type);
		ptr = ptr->next;
	}
}

bool	is_in(char *set, char c, int *index)
{
	int	i;

	i = -1;
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
