/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:02:06 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/06 06:54:07 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fds(t_msh *msh)
{
	close(msh->hd_fd_write);
	msh->hd_fd_write = -1;
	close(msh->historic_fd);
}

void	fake_redoc_process(char *eof, t_msh *msh)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, hd_signal_handle_fake);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line || !ft_strcmp(line, eof))
		{
			close(msh->historic_fd);
			free(line);
			break ;
		}
		free(line);
	}
	free_env(msh->env);
	free_env(msh->exp);
	clean_all(msh);
	exit(EXIT_SUCCESS);
}
