/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:27:06 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 12:37:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	restore(char sub, char *str, char res)
{
	while (*str)
	{
		if (*str == sub)
			*str = res;
		str++;
	}
}

static void	substite_pipe(char *str)
{
	char	quote;

	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
		}
		else if (*str == '|')
			*str = -1;
		str++;
	}
}

static void	substitute_spaces(char *str, char delimiter, char sub)
{
	while (*str && *str != delimiter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimiter)
	{
		if (is_in(SPACES, *str))
			*str = sub;
		str++;
	}
	if (*str)
	{
		str++;
		substitute_spaces(str, delimiter, sub);
	}
}

char	**split_single_input(char *str)
{
	char	**splitted;
	char	**ptr;

	substitute_spaces(str, '"', -1);
	substitute_spaces(str, '\'', -1);
	splitted = ft_split(str, ' ');
	ptr = splitted;
	while (*ptr)
	{
		restore(-1, *ptr, ' ');
		ptr++;
	}
	return (splitted);
}
