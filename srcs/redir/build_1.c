/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:16:18 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/23 16:21:40 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	last_redir_process(t_redir *list, t_type type)
{
	t_redir	*head;
	t_redir	*last;

	head = list;
	last = NULL;
	while (head)
	{
		if (head->absolute_type == type)
			last = head;
		head = head->next;
	}
	if (last)
	{
		last->is_last = true;
		head = list;
	}
}

void	check_last_redir(t_redir *list)
{
	last_redir_process(list, OUT);
	last_redir_process(list, IN);
}

int	heredoc_delimiter_len(char *str)
{
	int		count;
	int		i;
	char	quote;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
			{
				count++;
				i++;
			}
		}
		else
			count++;
	}
	return (count);
}

int	count_redir(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list)
	{
		if (token_list->type == REDIR_IN || token_list->type == TRUNC
			|| token_list->type == APPEND || token_list->type == HEREDOC)
			count++;
		token_list = token_list->next;
	}
	return (count);
}
