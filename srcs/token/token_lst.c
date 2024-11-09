/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:23:30 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 17:13:31 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*find_last_token(t_token *token_lst)
{
	while (token_lst->next)
		token_lst = token_lst->next;
	return (token_lst);
}

static char	*get_token(char *cmd, int *i)
{
	char	*result;
	char	quote;
	int		length;

	while (cmd[*i])
	{
		while (cmd[*i] && is_space(cmd[*i]))
			*i = *i + 1;
		if (cmd[*i] && (cmd[*i] == '\'' || cmd [*i] == '"'))
		{
			quote = cmd[*i];
			*i = *i + 1;
			length = customed_strlen(&cmd[*i], quote);
			result = ft_substr(cmd, *i, length);
			*i = *i + length + 1;
			return (result);
		}
		else if (cmd[*i] && !is_space(cmd[*i]))
		{
			length = customed_strlen(&cmd[*i], ' ');
			result = ft_substr(cmd, *i, length);
			*i += length;
			return (result);
		}
	}
	return (NULL);
}

static void	turn_cmd_into_tokens(char *cmd, t_token **token_lst)
{
	t_token	*new_token;
	t_token	*last_token;
	int		i;

	i = 0;
	while (cmd[i])
	{
		new_token = (t_token *) malloc(sizeof(t_token));
		//free if failed
		new_token->next = NULL;
		new_token->value = get_token(cmd, &i);
		if (*token_lst == NULL)
			*token_lst = new_token;
		else
		{
			last_token = find_last_token(*token_lst);
			last_token->next = new_token;
		}
	}
}

void	create_token_list(t_msh *msh)
{
	t_cmd	*current_cmd;
	t_token	*current_token;

	current_cmd = msh->cmd_lst;
	while (current_cmd)
	{
		current_cmd->token_lst = NULL;
		turn_cmd_into_tokens(current_cmd->value, &msh->cmd_lst->token_lst);
		current_cmd = current_cmd->next;
	}
	current_cmd = msh->cmd_lst;
	while (current_cmd)
	{
		current_token = current_cmd->token_lst;
		while (current_token)
		{
			printf("%s\n", current_token->value);
			current_token = current_token->next;
		}
		current_cmd = current_cmd->next;
	}
}
