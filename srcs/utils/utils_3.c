/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:42:41 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/23 16:48:45 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_var_list(t_var *head)
{
	t_var	*next;

	while (head)
	{
		next = head->next;
		free(head->varname);
		free(head->value);
		free(head);
		head = next;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}

void	free_redir_list(t_redir *head)
{
	t_redir	*next;

	while (head)
	{
		next = head->next;
		free(head->filename);
		free(head);
		head = next;
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free_tokens(head->token_list);
		if (head->argv)
			free_argv(head->argv);
		free_redir_list(head->redir_list);
		free(head);
		head = next;
	}
}

void	free_msh(t_msh *msh)
{
	free_cmds(msh->cmds);
}
