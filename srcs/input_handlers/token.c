/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:32:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/14 09:31:06 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_token(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (tokens[++i])
		count++;
	return (count);
}

static void	assign_type(t_token *new, char **prev)
{
	if (*prev && (!ft_strcmp(*prev, ">") || !ft_strcmp(*prev, ">>")))
		new->type = OUTFILE;
	else if (*prev && !ft_strcmp(*prev, "<"))
		new->type = INFILE;
	else if (*prev && !ft_strcmp(*prev, "<<"))
		new->type = EOF_HD;
	else if (!ft_strcmp(new->value, ">"))
		new->type = TRUNC;
	else if (!ft_strcmp(new->value, ">>"))
		new->type = APPEND;
	else if (!ft_strcmp(new->value, "<"))
		new->type = REDIR_IN;
	else if (!ft_strcmp(new->value, "<<"))
		new->type = HEREDOC;
	else
		new->type = WORD;
	if (*prev)
		free(*prev);
	*prev = ft_strdup(new->value);
}

static t_token	*get_last_node(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static void	add_token(t_token **head, char *token, int count, int i)
{
	t_token		*new;
	t_token		*last;
	static char	*prev = NULL;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(token);
	new->next = NULL;
	assign_type(new, &prev);
	if (*head == NULL)
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
	}
	if (count - 1 == i)
	{
		free(prev);
		prev = NULL;
	}
}

t_token	*create_token_list(char **tokens)
{
	t_token	*head;
	int		i;
	int		count;

	if (tokens == NULL)
		return (NULL);
	head = NULL;
	i = -1;
	count = count_token(tokens);
	while (tokens[++i])
		add_token(&head, tokens[i], count, i);
	return (head);
}
