/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/05 10:47:28 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_token(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
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
	t_token	*head;

	(void) ac,
	(void) av;
	(void) env;
	splitted = NULL;
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
				splitted = split_single_input(input);
			head = create_token_list(splitted);
			print_list(head);
			free_argv(splitted);
			free_token(head);
		}
		free(input);
	}
	return (0);
}
