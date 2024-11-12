/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/11 12:07:22 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	char	*prompt;
	t_cmd	*curr;
	t_token	*tok;

	(void) ac,
	(void) av;
	(void) env;
	prompt = get_prompt_cwd();
	msh.cmd = readline(prompt);
	msh.cmd_lst = NULL;
	unclosed_quote(msh.cmd, prompt);
	transform_quoted_pipe(msh.cmd, &msh);
	create_cmd_lst(msh.cmd, &msh);
	msh.i_qut_pipe = 0;
	restore_quoted_pipe(&msh);
	create_token_list(&msh);
	type_token(&msh);
	while (msh.cmd_lst)
	{
		curr = msh.cmd_lst;
		while (curr->token_lst)
		{
			tok = curr->token_lst->next;
			free(curr->token_lst->value);
			free(curr->token_lst);
			curr->token_lst = tok;
		}
		msh.cmd_lst = curr->next;
		free(curr->value);
		free(curr);
	}
	free(msh.pipe_pos);
	free(prompt);
	free(msh.cmd);
	return (0);
}
