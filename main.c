/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 20:53:04 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	while (1)
	{
		init_signal();
		input = readline("msh$ ");
		if (!input)
			exit(0);
		if (!has_obvious_syntax_error(input))
		{
			trim(&input);
			if (!has_pipe(input))
				splitted = split_single_input(input);
			head = create_token_list(splitted);
			print_list(head);
		}
		free(input);
	}
	return (0);
}
