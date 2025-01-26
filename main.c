/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/25 18:26:13 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	init_env(t_msh *msh, char **env)
{
	get_var_env(&msh->env, env);
	get_var_env(&msh->exp, env);
	sort_list_env(&msh->exp);
}

static void	msh_process(char *input, t_msh *msh, char **envp)
{
	if (!input)
	{
		free_env(msh->env);
		free_env(msh->exp);
		exit(0);
	}
	if (!has_obvious_syntax_error(input))
	{
		format_input(&input);
		if (!has_pipe(input))
			create_token_single_cmd(msh, input);
		else
			create_token_multi_cmds(msh, input);
		expand_variables(WORD, msh->cmds, msh->env);
		expand_variables(INFILE, msh->cmds, msh->env);
		expand_variables(OUTFILE, msh->cmds, msh->env);
		remove_quotes(msh);
		build_redir_list(msh);
		check_heredoc(msh);
		build_argv(msh);
		envp = get_env_arr(msh->env);
		minishell(msh, envp);
		free_argv(envp);
		clean_all(msh);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**envp;
	t_msh	msh;

	envp = NULL;
	init_env(&msh, env);
	(void) ac,
	(void) av;
	(void) env;
	while (1)
	{
		init_signal();
		input = readline("msh$ ");
		msh_process(input, &msh, envp);
	}
	return (0);
}
