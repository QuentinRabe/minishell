/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:22:21 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/17 10:45:00 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_heredoc(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list)
	{
		if (token_list->type == HEREDOC)
			count++;
		token_list = token_list->next;
	}
	return (count);
}

void	fake_heredoc(char *eof, t_msh *msh)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			line = readline("here_doc: ");
			if (!line || !ft_strcmp(line, eof))
			{
				printf("End Fake\n");
				free(line);
				break;
			}
			free(line);
		}
		free_env(msh->env);
		free_env(msh->exp);
		clean_all(msh);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

void	real_heredoc(char *eof, t_msh *msh, int heredoc_fd[2])
{
	pid_t	pid;
	char	*line;

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
				printf("End Real\n");
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

void	heredoc(char *eof, t_msh *msh, int heredoc_fd[2], int n)
{
	static int	i = 1;

	printf("[i->%d][n->%d]\n", i, n);
	if (i < n)
	{
		printf("Fake\n");
		fake_heredoc(eof, msh);
		i++;
		return ;
	}
	else
	{
		printf("Real\n");
		real_heredoc(eof, msh, heredoc_fd);
		i = 1;
		return ;
	}
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
	int		heredocs;

	cmd = msh->cmds;
	while (cmd)
	{
		init_fds(cmd->heredoc_fd);
		token = cmd->token_list;
		heredocs = count_heredoc(token);
		while (token)
		{
			if (heredocs == 0)
				break ;
			if (token->type == HEREDOC)
				heredoc(token->next->value, msh, cmd->heredoc_fd, heredocs);
			token = token->next;
		}
		if (heredocs)
		{
			printf("Heredoc_fd[0] = [%d]\n", cmd->heredoc_fd[0]);
			close(cmd->heredoc_fd[0]);
		}
		cmd = cmd->next;
	}
}
