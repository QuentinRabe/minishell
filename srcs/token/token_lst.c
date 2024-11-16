/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 06:26:28 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/12 10:15:48 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:23:30 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/11 11:16:56 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	find_arrow(char *str)
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

static t_bool	is_there_arrow(char *str)
{
	while (*str && *str != ' ')
	{
		if (*str == '<' || *str == '>')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

static int	count_arrow(char *str, char arrow)
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

static t_token	*find_last_token(t_token *token_lst)
{
	while (token_lst->next)
		token_lst = token_lst->next;
	return (token_lst);
}

static char	*extract_token(char *cmd, int *i, char delimiter, t_token *token)
{
	int		length;
	char	*result;

	if ((delimiter == '<' || delimiter == '>') && (cmd[*i] == '<' || cmd[*i] == '>'))
		length = count_arrow(&cmd[*i], delimiter);
	else
		length = customed_strlen(&cmd[*i], delimiter);
	if (delimiter == '"')
	{
		token->in_d_quote = TRUE;
		token->in_s_quote = FALSE;
	}
	else if (delimiter == '\'')
	{
		token->in_s_quote = TRUE;
		token->in_d_quote = FALSE;
	}
	else
	{
		token->in_d_quote = FALSE;
		token->in_s_quote = FALSE;
	}
	result = ft_substr(cmd, *i, length);
	if (!result)
		return (NULL);
	*i += length;
	if (cmd[*i] == delimiter && (delimiter != '<' && delimiter != '>'))
		(*i)++;
	return (result);
}

static char	*get_token(char *cmd, int *i, t_token *token)
{
	char	quote;
	char	arrow;

	while (cmd[*i])
	{
		while (cmd[*i] && is_space(cmd[*i]))
			*i = *i + 1;
		if (cmd[*i] && (cmd[*i] == '\'' || cmd [*i] == '"'))
		{
			quote = cmd[*i];
			*i = *i + 1;
			return (extract_token(cmd, i, quote, token));
		}
		else if (cmd[*i] && !is_space(cmd[*i]))
		{
			if (is_there_arrow(&cmd[*i]))
			{
				arrow = find_arrow(&cmd[*i]);
				return (extract_token(cmd, i, arrow, token));
			}
			else
				return (extract_token(cmd, i, ' ', token));
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
		new_token->next = NULL;
		new_token->value = get_token(cmd, &i, new_token);
		if (!new_token->value)
			return (free(new_token));
		if (*token_lst == NULL)
		{
			*token_lst = new_token;
			new_token->prev = NULL;
		}
		else
		{
			last_token = find_last_token(*token_lst);
			last_token->next = new_token;
			new_token->prev = last_token;
		}
	}
}

void	create_token_list(t_msh *msh)
{
	t_cmd	*current_cmd;

	current_cmd = msh->cmd_lst;
	while (current_cmd)
	{
		current_cmd->token_lst = NULL;
		turn_cmd_into_tokens(current_cmd->value, &msh->cmd_lst->token_lst);
		current_cmd = current_cmd->next;
	}
}
