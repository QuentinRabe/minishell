/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:32:08 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/18 13:32:08 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

char	check_for_delimiter(char *str)
{
	while (*str && *str != ' ')
	{
		if (*str == '"' || *str == '\'')
			return (*str);
		str++;
	}
	return (' ');
}

char	find_arrow(char *str)
{
	while (*str && *str != ' ')
	{
		if (*str == '<' || *str == '>')
		{
			return (*str);
		}
		str++;
	}
	return (0);
}

t_bool	is_there_arrow(char *str)
{
	while (*str && *str != ' ')
	{
		if (*str == '<' || *str == '>')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	count_arrow(char *str, char arrow)
{
	int	counter;

	counter = 0;
	while (*str && *str == arrow)
	{
		counter++;
		str++;
	}
	return (counter);
}

t_token	*find_last_token(t_token *token_lst)
{
	while (token_lst->next)
		token_lst = token_lst->next;
	return (token_lst);
}
