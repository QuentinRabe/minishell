/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 07:27:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/21 07:27:41 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_word(t_token *token)
{
	int		counter;
	t_token	*curr_token;

	counter = 0;
	curr_token = token;
	while (curr_token)
	{
		printf("token -> %s\n", curr_token->value);
		if (curr_token->kind == WORD)
		{
			counter++;
		}
		curr_token = curr_token->next;
	}
	return (counter);
}

static void	take_token_word(char ***argv, t_token *token_lst)
{
	int		i;
	t_token	*curr_token;

	i = 0;
	curr_token = token_lst;
	while (curr_token)
	{
		if (curr_token->kind == WORD)
			(*argv)[i++] = ft_strdup(curr_token->value);
		curr_token = curr_token->next;
	}
	(*argv)[i] = NULL;
}

void	build_argv(t_msh *msh)
{
	t_cmd	*curr_cmd;
	int		i;
	// t_token	*curr_token;
	int		args;

	curr_cmd = msh->cmd_lst;
	while (curr_cmd)
	{
		printf("cmd value -> %s\n", curr_cmd->value);
		args = count_word(curr_cmd->token_lst);
		printf("there are %d args\n", args);
		curr_cmd->argv = (char **) malloc((args + 1) * sizeof(char *));
		take_token_word(&curr_cmd->argv, curr_cmd->token_lst);
		curr_cmd = curr_cmd->next;
	}
	curr_cmd = msh->cmd_lst;
	while (curr_cmd)
	{
		i = -1;
		printf("=======================================\n");
		while (curr_cmd->argv[++i])
			printf("%s\n", curr_cmd->argv[i]);
		curr_cmd = curr_cmd->next;
	}
}