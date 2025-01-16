/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:22:21 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/16 09:36:30 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc(char *eof, t_msh *msh, int heredoc_fd[2])
{
	pid_t	pid;
	char	*line;

	if (heredoc_fd[0] != -1 && heredoc_fd[1] != -1)
	{
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
	}
	if (pipe(heredoc_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		close(heredoc_fd[0]);
		while (1)
		{
			line = readline("here_doc: ");
			if (!line || !ft_strcmp(line, eof))
			{
				free(line);
				break;
			}
			write(heredoc_fd[1], line, ft_strlen(line));
			write(heredoc_fd[1], "\n", 1);
			free(line);
		}
		close(heredoc_fd[1]);
		free_env(msh->env);
		free_env(msh->exp);
		clean_all(msh);
		exit(EXIT_SUCCESS);
	}
	close(heredoc_fd[1]);
	wait(NULL);
}

void	init_fds(int heredoc_fd[2])
{
	heredoc_fd[0] = -1;
	heredoc_fd[1] = -1;
}
void	check_heredoc(t_msh	*msh)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = msh->cmds;
	while (cmd)
	{
		init_fds(cmd->heredoc_fd);
		token = cmd->token_list;
		while (token)
		{
			if (token->type == HEREDOC)
			{
				heredoc(token->next->value, msh, cmd->heredoc_fd);
				printf("heredocfd0->[%d]\nheredocfd1->[%d]\n", cmd->heredoc_fd[0], cmd->heredoc_fd[1]);
			}
			token = token->next;
		}
		if (cmd->heredoc_fd[0] != -1 && cmd->heredoc_fd[1] != -1)
		{
			close(cmd->heredoc_fd[0]);
			close(cmd->heredoc_fd[1]);
		}
		cmd = cmd->next;
	}
}
