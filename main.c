/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/07 13:43:43 by arabefam         ###   ########.fr       */
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
		// free_var_list(head->var_list);
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
		free(head);
		head = next;
	}
}

void	free_msh(t_msh *msh)
{
	t_cmd	*curr;

	curr = msh->cmds;
	while (curr)
	{
		free_tokens(curr->token_lis);
		curr = curr->next;
	}
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

void	clean_all(t_msh *msh, char ***inputs)
{
	char	***tmp;

	tmp = inputs;
	while (*tmp)
	{
		free_argv(*tmp);
		tmp++;
	}
	free(inputs);
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
	char	***splitted;
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
				splitted = create_token_single_cmd(&msh, input);
			else
				splitted = create_token_multi_cmds(&msh, input);
			// expand_variables(WORD, msh.cmds, msh.env);
			print_list(msh.cmds);
			clean_all(&msh, splitted);
		}
		free(input);
	}
	return (0);
}
