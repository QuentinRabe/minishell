/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 09:53:05 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

void	free_env(t_e_env *env)
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

void	reset_token(t_msh *msh)
{
	t_cmd	*curr;
	t_token	*tok;

	if (msh->pipe_pos)
		free(msh->pipe_pos);
	while (msh->cmd_lst)
	{
		curr = msh->cmd_lst;
		while (curr->token_lst)
		{
			tok = curr->token_lst->next;
			free(curr->token_lst->value);
			free(curr->token_lst);
			curr->token_lst = tok;
		}
		free_argv(msh->cmd_lst->argv);
		msh->cmd_lst = curr->next;
		free(curr->value);
		free(curr);
	}
	free(msh->cmd);
}

void	tokenization(t_msh *msh)
{
	create_cmd_lst(msh->cmd, msh);
	msh->i_qut_pipe = 0;
	restore_quoted_pipe(msh);
	create_token_list(msh);
	type_token(msh);
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;

	(void) ac,
	(void) av;
	(void) env;
	init_env(&msh, env);
	msh.ex_status = 0;
	while (1)
	{
		msh.cmd = readline("$>");
		msh.cmd_lst = NULL;
		if (!check_obvious_error(msh.cmd, &msh))
		{
			reset(&msh);
			continue;
		}
		tokenization(&msh);
		expand_vars(&msh, WORD);
		build_argv(&msh);
		reset_token(&msh);
		break;
	}
	free_env(msh.env_data.env);
	free_env(msh.env_data.ex_env);
	return (0);
}
