/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_multi_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:22:24 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/16 10:36:51 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd	*get_last_node(t_cmd *head)
{
	t_cmd	*ptr;

	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	treat_each_cmd(t_cmd **head, char *cmd)
{
	t_cmd	*new;
	t_cmd	*last;
	char	**splitted;

	new = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new)
		return ;
	splitted = split_single_input(cmd);
	new->value = ft_strdup(cmd);
	new->argv = NULL;
	new->token_list = create_token_list(splitted);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
	}
	free_argv(splitted);
}

void	create_token_multi_cmds(t_msh *msh, char *input)
{
	char	**splitted;
	int		i;

	splitted = split_multi_input(input);
	free(input);
	msh->cmds = NULL;
	i = -1;
	while (splitted[++i])
		treat_each_cmd(&msh->cmds, splitted[i]);
	free_argv(splitted);
}
