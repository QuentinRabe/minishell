/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:32:39 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 20:21:30 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	*prev = new->value;
}

static t_token	*get_last_node(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static void	add_token(t_token **head, char *token)
{
	t_token		*new;
	t_token		*last;
	static char	*prev = NULL;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = token;
	new->next = NULL;
	assign_type(new, &prev);
	if (*head == NULL)
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
	}
}

t_token	*create_token_list(char **tokens)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = -1;
	while (tokens[++i])
		add_token(&head, tokens[i]);
	return (head);
}
