/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:58:51 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/19 09:11:18 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	skip_quotes(char *str, char quote)
{
	str++;
	while (*str && *str != quote)
		str++;
}

bool	has_redir_without_filname(char *str)
{
	char	arrow;

	while (*str)
	{
		if (*str == '\'' || *str == '"')
			skip_quotes(str, *str);
		else if (*str == '>' || *str == '<')
		{
			arrow = *str++;
			if (*str && *str == arrow)
				continue ;
			while (is_in(SPACES, *str, NULL))
				str++;
			if (*str == '\0')
				return (ft_putendl_fd(ERRSYNT"`newline'", 2), true);
			if (*str && *str == '|')
				return (ft_putendl_fd(ERRSYNT"`|'", 2), true);
		}
		if (*str)
			str++;
	}
	return (false);
}
