/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:33:47 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/11 11:27:52 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	in_pipe_arr(t_msh *msh, int val)
{
	int	i;

	i = -1;
	while (++i < msh->quoted_pipe)
	{
		if (val == msh->pipe_pos[i])
			return (TRUE);
	}
	return (FALSE);
}

t_bool	end_with_quote(char *str, char quote)
{
	if (*str == 0)
		return (FALSE);
	while (*str && *str != quote)
		str++;
	return (*str == quote);
}

void	count_pipe_in_substr(char *substr, int *counter)
{
	while (*substr)
	{
		if (*substr == '|')
			*counter += 1;
		substr++;
	}
}

int	count_quoted_pipe(char *str)
{
	int		i;
	char	*sub;
	int		counter;
	char	quote;

	i = -1;
	counter = 0;
	while (str[++i])
	{
		if (str[i] && str[i + 1] && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			if (str[i] && end_with_quote(&str[i + 1], quote))
			{
				i++;
				sub = ft_substr(str, i, customed_strlen(&str[i], quote));
				count_pipe_in_substr(sub, &counter);
				i += customed_strlen(&str[i], quote);
				if (str[i + 1])
					i += 1;
				free(sub);
			}
		}
	}
	return (counter);
}
