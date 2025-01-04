/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:29:11 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 20:51:56 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_too_much_arrows(char *str)
{
	char	arrow;
	char	quote;
	int		count;

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
			arrow = *str;
			count = 0;
			while (*str && *str++ == arrow)
				count++;
			if (count > 2)
				return (printf(ERRSYNT"`%c'\n", arrow), true);
		}
		str++;
	}
	return (false);
}
