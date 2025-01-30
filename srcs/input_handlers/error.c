/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:28:20 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/30 11:29:51 by arabefam         ###   ########.fr       */
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
			quote = *str++;
			while (*str && *str != quote)
				str++;
		}
		else if (*str == '|')
		{
			str++;
			while (*str && is_in(SPACES, *str, NULL))
				str++;
			if (*str == '|')
			{
				ft_putendl_fd(ERRSYNT"`|'", 2);
				return (true);
			}
		}
		if (*str)
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
				ft_putstr_fd(ERRSYNT"`", 2);
				ft_putstr_fd(&quote, 2);
				ft_putendl_fd("'", 2);
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
		ft_putendl_fd(ERRSYNT"`|'", 2);
		result = !result;
	}
	return (result);
}

bool	has_obvious_syntax_error(char *str)
{
	char	*trim;
	bool	result;
	t_msh	*msh;

	result = false;
	msh = get_msh(1, NULL);
	if (ft_strlen(str))
	{
		trim = ft_strtrim(str, SPACES);
		if (has_extrem_pipe(trim) || has_successive_pipe(trim)
			|| has_unclosed_quote(trim) || has_too_much_arrows(trim)
			|| has_consecutive_opps_arrows(trim)
			|| has_redir_without_filname(trim))
		{
			msh->status = 2;
			add_history(str);
			result = !result;
		}
		free(trim);
	}
	return (result);
}
