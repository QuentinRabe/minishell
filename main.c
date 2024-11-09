/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/09 14:49:40 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	char	*prompt;
	t_cmd	*curr;

	(void) ac,
	(void) av;
	(void) env;
	prompt = get_prompt_cwd();
	msh.cmd = readline(prompt);
	msh.cmd_lst = NULL;
	transform_quoted_pipe(msh.cmd, &msh);
	create_cmd_lst(msh.cmd, &msh);
	// create_token_list(&msh);

	while (msh.cmd_lst)
	{
		curr = msh.cmd_lst;
		msh.cmd_lst = curr->next;
		printf("%s\n", curr->value);
		free(curr->value);
		free(curr);
	}
	free(msh.pipe_pos);
	free(prompt);
	free(msh.cmd);
	return (0);
}
