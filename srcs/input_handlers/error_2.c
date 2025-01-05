/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:58:51 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/05 14:04:13 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_redir_without_filname(char *str)
{
	char	arrow;
	char	quote;

	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str++;
			while (*str && *str != quote)
				str++;
		}
		else if (*str == '>' || *str == '<')
		{
			arrow = *str++;
			if (*str && *str == arrow)
				continue;
			while (is_in(SPACES, *str, NULL))
				str++;
			if (*str == '\0')
				return (printf(ERRSYNT"`newline'\n"), true);
			if (*str && *str == '|')
				return (printf(ERRSYNT"`|'\n"), true);
		}
		str++;
	}
	return (false);
}
