/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:50:44 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/08 08:38:14 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	count_spaces_around(char *str, int i, int *count)
{
	if ((i - 1) > 0 && (str[i - 1] && !is_in(SPACES, str[i - 1], NULL) && str[i - 1] != str[i]))
		*count += 1;
	if (str[i + 1] && str[i + 1] != str[i] && !is_in(SPACES, str[i + 1], NULL))
		*count += 1;
}

int	count_additionnal_spaces(char *str)
{
	char	quote;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			count_spaces_around(str, i, &count);
		i++;
	}
	return (count);
}
