/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:14:22 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/03 13:05:59 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_words(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list)
	{
		if (token_list->type == WORD)
			count++;
		token_list = token_list->next;
	}
	return (count);
}

char	**take_words(t_token *token_list)
{
	char	**argv;
	int		len;
	int		i;

	len = count_words(token_list);
	argv = (char **) malloc((len + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (token_list && !token_list->value[0] && !token_list->in_dq)
		token_list = token_list->next;
	while (token_list)
	{
		if (token_list->type == WORD)
			argv[i++] = ft_strdup(token_list->value);
		token_list = token_list->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	build_argv(t_msh *msh)
{
	t_cmd	*curr_cmd;

	curr_cmd = msh->cmds;
	while (curr_cmd)
	{
		curr_cmd->argv = take_words(curr_cmd->token_list);
		curr_cmd = curr_cmd->next;
	}
	curr_cmd = msh->cmds;
}
