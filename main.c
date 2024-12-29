/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2024/12/29 12:18:00 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_env(t_e_env *env)
{
	t_e_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	char	*prompt;
	t_cmd	*curr;
	t_token	*tok;

	(void) ac,
	(void) av;
	(void) env;
	msh.ex_status = 0;
	prompt = get_prompt_cwd();
	msh.cmd = readline(prompt);
	msh.cmd_lst = NULL;
	check_obvious_error(msh.cmd, &msh);
	unclosed_quote(msh.cmd, prompt);
	transform_quoted_pipe(msh.cmd, &msh);
	successive_pipe(msh.cmd, prompt,  &msh);
	create_cmd_lst(msh.cmd, &msh);
	msh.i_qut_pipe = 0;
	restore_quoted_pipe(&msh);
	create_token_list(&msh);
	type_token(&msh);
	create_env_lst(&msh.env_data.env, env);
	expand_vars(&msh);
	// build_argv(&msh);
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
	free_env(msh.env_data.env);
	free(msh.pipe_pos);
	free(prompt);
	free(msh.cmd);
	return (0);
}
