/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:22:21 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/16 08:03:02 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc(t_cmd *cmd, char *eof, t_msh *msh)
{
	int		pipefd[2];
	pid_t	pid;
	char	*line;

	if (pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			line = readline("here_doc: ");
			if (!line || !ft_strcmp(line, eof))
			{
				free(line);
				break;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		free_env(msh->env);
		free_env(msh->exp);
		clean_all(msh);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	cmd->heredoc_fd = dup(pipefd[0]);
	close(pipefd[0]);
	wait(NULL);
}

void	check_heredoc(t_msh	*msh)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = msh->cmds;
	while (cmd)
	{
		token = cmd->token_lis;
		while (token)
		{
			if (token->type == HEREDOC)
			{
				heredoc(cmd, token->next->value, msh);
				printf("heredocfd->[%d]\n", cmd->heredoc_fd);
			}
			token = token->next;
		}
		cmd = cmd->next;
	}
}
