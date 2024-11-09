/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/09 13:41:46 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	char	*prompt;

	(void) ac,
	(void) av;
	(void) env;
	prompt = get_prompt_cwd();
	msh.cmd = readline(prompt);
	msh.cmd_lst = NULL;
	// create_cmd_lst(msh.cmd, &msh);
	// create_token_list(&msh);
	transform_quoted_pipe(msh.cmd, &msh);
	printf("%s\n", msh.cmd);
	free(msh.pipe_pos);
	free(prompt);
	free(msh.cmd);
	return (0);
}
