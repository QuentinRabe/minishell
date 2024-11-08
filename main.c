/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:26 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 10:48:34 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_msh	msh;

	(void) ac,
	(void) av;
	(void) env;
	msh.cmd_arr = NULL;
	while (1)
	{
		msh.cmd = readline(get_prompt_cwd());
		if (ft_strlen(msh.cmd) == 0)
			continue;
		add_history(msh.cmd);
		init_tokenization(msh.cmd, msh.cmd_arr);
	}
	return (0);
}
