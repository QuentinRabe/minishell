/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/22 13:05:35 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_var_list(t_var *head)
{
	t_var	*next;

	while (head)
	{
		next = head->next;
		free(head->varname);
		free(head->value);
		free(head);
		head = next;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}
void	free_redir_list(t_redir *head)
{
	t_redir	*next;

	while (head)
	{
		next = head->next;
		free(head->filename);
		free(head);
		head = next;
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free_tokens(head->token_list);
		if (head->argv)
			free_argv(head->argv);
		free_redir_list(head->redir_list);
		free(head);
		head = next;
	}
}

void	free_msh(t_msh *msh)
{
	free_cmds(msh->cmds);
}

void	free_env(t_var_env *env)
{
	t_var_env	*curr;
	t_var_env	*next;

	curr = env;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

void	clean_all(t_msh *msh)
{
	free_msh(msh);
}

void	signal_handler(int sig)
{
	if (sig)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_msh	msh;

	(void) ac,
	(void) av;
	(void) env;
	get_var_env(&msh.env, env);
	get_var_env(&msh.exp, env);
	sort_list_env(&msh.exp);
	while (1)
	{
		init_signal();
		input = readline("msh$ ");
		if (!input)
		{
			free_env(msh.env);
			free_env(msh.exp);
			exit(0);
		}
		if (!has_obvious_syntax_error(input))
		{
			format_input(&input);
			if (!has_pipe(input))
				create_token_single_cmd(&msh, input);
			else
				create_token_multi_cmds(&msh, input);
			expand_variables(WORD, msh.cmds, msh.env);
			expand_variables(INFILE, msh.cmds, msh.env);
			expand_variables(OUTFILE, msh.cmds, msh.env);
			remove_quotes(&msh);
			build_redir_list(&msh);
			check_heredoc(&msh);
			build_argv(&msh);
			// minishell(&msh, env);
			clean_all(&msh);
		}
	}
	return (0);
}
