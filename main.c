/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/05 11:38:54 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
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

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
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
	char	**splitted;
	t_msh	msh;

	(void) ac,
	(void) av;
	(void) env;
	while (1)
	{
		init_signal();
		input = readline("msh$ ");
		if (!input)
			exit(0);
		if (!has_obvious_syntax_error(input))
		{
			format_input(&input);
			if (!has_pipe(input))
				splitted = create_token_single_cmd(&msh, input);
			print_list(msh.cmds->token_lis);
			free_argv(splitted);
			free_msh(&msh);
		}
		free(input);
	}
	return (0);
}
