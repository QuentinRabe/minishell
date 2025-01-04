/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:16:04 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 12:16:14 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_pipe(char *str)
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
			return (true);
		str++;
	}
	return (false);
}
