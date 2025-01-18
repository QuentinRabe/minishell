/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:22:21 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/18 09:55:21 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_there_heredoc(t_redir *list)
{
	while (list)
	{
		if (list->type == HEREDOC)
			return (true);
		list = list->next;
	}
	return (false);
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

void	heredoc(t_redir *list, t_msh *msh)
{
	static int	i = 1;

	if (!list->is_last)
	{
		fake_heredoc(list->filename, msh);
		i++;
		return ;
	}
	else
	{
		real_heredoc(list->filename, msh, list->heredoc_fd);
		i = 1;
		return ;
	}
}

void	check_heredoc(t_msh	*msh)
{
	t_cmd	*cmd;
	t_redir	*list;

	cmd = msh->cmds;
	while (cmd)
	{
		list = cmd->redir_list;
		if (is_there_heredoc(list))
		{
			while (list)
			{
				if (list->type == HEREDOC)
					heredoc(list, msh);
				list = list->next;
			}
		}
		// if (heredocs)
		// {
		// 	printf("Heredoc_fd[0] = [%d]\n", cmd->heredoc_fd[0]);
		// 	close(cmd->heredoc_fd[0]);
		// }
		cmd = cmd->next;
	}
}
