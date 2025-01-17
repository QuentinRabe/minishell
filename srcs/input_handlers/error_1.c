/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:29:11 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/17 13:05:01 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	opposite_of(char arrow)
{
	if (arrow == '>')
		return ('<');
	return ('>');
}

static void	print_arrow_error(char arrow)
{
	ft_putstr_fd(ERRSYNT"`", 2);
	ft_putstr_fd(&arrow, 2);
	ft_putendl_fd("'\n", 2);
}

bool	has_consecutive_opps_arrows(char *str)
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
			arrow = *str;
			str++;
			if (*str && *str == opposite_of(arrow))
				return (print_arrow_error(arrow), true);
		}
		if (*str)
			str++;
	}
	return (false);
}

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
				return (print_arrow_error(arrow), true);
		}
		if (*str)
			str++;
	}
	return (false);
}
