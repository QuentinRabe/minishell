/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:42:59 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/12 07:42:59 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*str_type(int type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == TRUNC)
		return ("TRUNC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == INFILE)
		return ("INFILE");
	else if (type == OUTFILE)
		return ("OUTFILE");
	else if (type == EOF_HD)
		return ("EOF_HEREDOC");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	return (NULL);
}

static void	check_redir_file_type(t_token *token)
{
	if (token->kind == WORD && token->prev && token->prev->kind == REDIR_IN)
		token->kind = INFILE;
	else if (token->kind == WORD && token->prev && token->prev->kind == HEREDOC)
		token->kind = EOF_HD;
	else if (token->kind == WORD && token->prev && token->prev->kind == TRUNC)
		token->kind = OUTFILE;
	else if (token->kind == WORD && token->prev && token->prev->kind == APPEND)
		token->kind = OUTFILE;
}

static void	give_type_token(char *token, t_token *token_lst)
{
	if (!ft_strncmp(token, "<<", 2))
		token_lst->kind = HEREDOC;
	else if (!ft_strncmp(token, ">>", 2))
		token_lst->kind = APPEND;
	else if (!ft_strncmp(token, ">", 1))
		token_lst->kind = TRUNC;
	else if (!ft_strncmp(token, "<", 1))
		token_lst->kind = REDIR_IN;
	else
		token_lst->kind = WORD;
}

void	type_token(t_msh *msh)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;

	curr_cmd = msh->cmd_lst;
	while (curr_cmd)
	{
		curr_token = curr_cmd->token_lst;
		while (curr_token)
		{
			give_type_token(curr_token->value, curr_token);
			check_redir_file_type(curr_token);
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	curr_cmd = msh->cmd_lst;
	while (curr_cmd)
	{
		curr_token = curr_cmd->token_lst;
		while (curr_token)
		{
			printf("[value %s type %s In double quote = %d]\n", curr_token->value, str_type(curr_token->kind), curr_token->in_d_quote);
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
}