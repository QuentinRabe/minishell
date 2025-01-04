/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:28:20 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 21:57:59 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	has_successive_pipe(char *str)
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
		{
			str++;
			while (*str && is_in(SPACES, *str, NULL))
				str++;
			if (*str == '|')
				printf(ERRSYNT"`|'\n");
			return (true);
		}
		str++;
	}
	return (false);
}

static bool	has_unclosed_quote(char *str)
{
	char	quote;
	bool	result;

	result = false;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			str++;
			result = false;
			while (*str && *str != quote)
				str++;
			if (*str == '\0')
			{
				result = true;
				printf(ERRSYNT"`%c'\n", quote);
				break ;
			}
		}
		str++;
	}
	return (result);
}

static bool	has_extrem_pipe(char *str)
{
	int		end_index;
	bool	result;

	end_index = ft_strlen(str) - 1;
	result = false;
	if (str[0] == '|' || str[end_index] == '|')
	{
		printf(ERRSYNT"`|'\n");
		result = !result;
	}
	return (result);
}

bool	has_obvious_syntax_error(char *str)
{
	char	*trim;
	bool	result;

	result = false;
	trim = ft_strtrim(str, SPACES);
	if (has_extrem_pipe(trim) || has_successive_pipe(trim)
		|| has_unclosed_quote(trim) || has_too_much_arrows(trim)
		|| has_consecutive_opps_arrows(trim))
		result = !result;
	free(trim);
	return (result);
}
