/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:08 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/23 16:28:36 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_redir	*get_last_node(t_redir *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

static char	*heredoc_delimiter(char *str, t_redir *old, char *filename)
{
	int		len;
	char	*new;

	len = heredoc_delimiter_len(str);
	new = (char *) malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	create_delimiter(new, str);
	if (ft_strcmp(new, filename))
		old->expand = false;
	return (new);
}

void	create_redir_list_process(t_type type, char *filename, \
t_redir *new)
{
	char	*tmp;

	new->next = NULL;
	new->expand = true;
	new->filename = ft_strdup(filename);
	new->type = type;
	if (type == HEREDOC || type == REDIR_IN)
	{
		tmp = ft_strdup(new->filename);
		free(new->filename);
		new->filename = heredoc_delimiter(filename, new, tmp);
		free(tmp);
		new->absolute_type = IN;
	}
	else
		new->absolute_type = OUT;
	new->is_last = false;
	new->heredoc_fd[0] = -1;
	new->heredoc_fd[1] = -1;
}

void	create_redir_list(t_redir **redir_list, t_type type, char *filename)
{
	t_redir	*new;
	t_redir	*last;

	new = (t_redir *) malloc(sizeof(t_redir));
	if (!new)
		return ;
	create_redir_list_process(type, filename, new);
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
					create_redir_list(&curr_cmd->redir_list, \
					curr_tok->type, curr_tok->next->value);
					curr_tok = curr_tok->next;
				}
				if (curr_tok)
					curr_tok = curr_tok->next;
			}
			check_last_redir(curr_cmd->redir_list);
		}
		curr_cmd = curr_cmd->next;
	}
}
