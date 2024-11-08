/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:16:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 10:42:03 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	increase_counter_token(char *str, int *counter, int *index)
{
	char	quote;

	if ((str[*index] == '\'' || str[*index] == '"') && str[*index])
	{
		*counter += 1;
		quote = str[*index];
		*index += 1;
		while (str[*index] != quote && str[*index])
			*index += 1;
		if (str[*index] == quote)
			*index += 1;
	}
	else
	{
		*counter += 1;
		while (str[*index] && !is_space(str[*index]))
			*index += 1;
	}
}

int	customed_strlen(char *str, char charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] != charset)
	{
		i++;
		counter++;
	}
	return (counter);
}

void	skip_space(char *str, int *index)
{
	while (str[*index] && is_space(str[*index]))
		*index += 1;
}

int	count_cmds(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		;
	return (i);
}

int count_tokens(char *str)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		skip_space(str, &i);
		increase_counter_token(str, &counter, &i);
	}
	return (counter);
}
