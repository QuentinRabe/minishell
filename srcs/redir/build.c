/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:08 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/17 12:52:44 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_redir	*get_last_node(t_redir *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

static int	count_redir(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list)
	{
		if (token_list->type == REDIR_IN || token_list->type == TRUNC
			|| token_list->type == APPEND)
			count++;
		token_list = token_list->next;
	}
	return (count);
}

void	create_redir_list(t_redir **redir_list, t_type type, char *filename)
{
	t_redir	*new;
	t_redir	*last;

	new = (t_redir *) malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->next = NULL;
	new->expand = true;
	new->filename = filename;
	new->type = type;
	new->heredoc_fd[0] = -1;
	new->heredoc_fd[1] = -1;
	if (*redir_list == NULL)
		*redir_list = new;
	else
	{
		last = get_last_node(*redir_list);
		last->next = new;
	}
}

void	build_redir_list(t_msh *msh)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	t_redir	*curr_redir;

	curr_cmd = msh->cmds;
	while (curr_cmd)
	{
		curr_cmd->redir_list = NULL;
		if (count_redir(curr_cmd->token_list))
		{
			curr_tok = curr_cmd->token_list;
			while (curr_tok)
			{
				if (curr_tok->type != WORD)
				{
					create_redir_list(&curr_cmd->redir_list, curr_tok->type, curr_tok->next->value);
					curr_tok = curr_tok->next;
				}
				if (curr_tok)
					curr_tok = curr_tok->next;
			}
		}
		curr_cmd = curr_cmd->next;
	}
	//print redir_list
	curr_cmd = msh->cmds;
	while (curr_cmd)
	{
		if (count_redir(curr_cmd->token_list))
		{
			curr_redir = curr_cmd->redir_list;
			printf("[REDIR]\n");
			while (curr_redir)
			{
				printf("[%d][%s]", curr_redir->type, curr_redir->filename);
				curr_redir = curr_redir->next;
			}
			printf("\n");
		}
		curr_cmd = curr_cmd->next;
	}
}
