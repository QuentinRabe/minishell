/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_multi_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:22:24 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/10 09:32:10 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_cmds(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

static t_cmd	*get_last_node(t_cmd *head)
{
	t_cmd	*ptr;

	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static char	**treat_each_cmd(t_cmd **head, char *cmd)
{
	t_cmd	*new;
	t_cmd	*last;
	char	**splitted;

	new = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	splitted = split_single_input(cmd);
	new->value = cmd;
	new->token_lis = create_token_list(splitted);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
	}
	return (splitted);
}

char	***create_token_multi_cmds(t_msh *msh, char *input)
{
	char	**splitted;
	char	***ptr;
	int		i;

	splitted = split_multi_input(input);
	free(input);
	ptr = (char ***) malloc((count_cmds(splitted) + 1) * sizeof(char **));
	if (!ptr)
		return (NULL);
	msh->cmds = NULL;
	i = -1;
	while (splitted[++i])
		ptr[i] = treat_each_cmd(&msh->cmds, splitted[i]);
	ptr[i] = NULL;
	free_argv(splitted);
	return (ptr);
}
