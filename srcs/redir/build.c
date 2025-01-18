/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:08 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/18 10:46:35 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_last_redir(t_redir *list)
{
	t_redir	*head;
	t_redir	*last;

	head = list;
	last = NULL;
	while (head)
	{
		if (head->absolute_type == OUT)
			last = head;
		head = head->next;
	}
	if (last)
	{
		last->is_last = true;
		head = list;
	}
	head = list;
	last = NULL;
	while (head)
	{
		if (head->absolute_type == IN)
			last = head;
		head = head->next;
	}
	if (last)
	{
		last->is_last = true;
		head = list;
	}
}

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
			|| token_list->type == APPEND || token_list->type == HEREDOC)
			count++;
		token_list = token_list->next;
	}
	return (count);
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

static void	create_delimiter(char *new, char *old)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '\'' || old[i] == '"')
		{
			quote = old[i];
			i++;
			while (old[i] && old[i] != quote)
			{
				new[j] = old[i];
				j++;
				i++;
			}
		}
		else
		{
			new[j] = old[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
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

void	create_redir_list(t_redir **redir_list, t_type type, char *filename)
{
	t_redir	*new;
	t_redir	*last;
	char	*tmp;

	new = (t_redir *) malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->next = NULL;
	new->expand = true;
	new->filename = ft_strdup(filename);
	new->type = type;
	if (type == HEREDOC || type == REDIR_IN)
	{
		tmp = ft_strdup(new->filename);
		free(new->filename);
		new->filename = heredoc_delimiter(filename, new, tmp);
		printf("[heredoc del = %s]\n", new->filename);
		free(tmp);
		new->absolute_type = IN;
	}
	else
		new->absolute_type = OUT;
	new->is_last = false;
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
			check_last_redir(curr_cmd->redir_list);
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
				printf("[%d][%s][last%d][expand%d]", curr_redir->type, curr_redir->filename, curr_redir->is_last, curr_redir->expand);
				curr_redir = curr_redir->next;
			}
			printf("\n");
		}
		curr_cmd = curr_cmd->next;
	}
}
