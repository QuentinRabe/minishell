/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:22:21 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/06 09:22:59 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	fake_heredoc(char *eof, t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, reset_sig);
	if (pid == 0)
		fake_redoc_process(eof, msh);
	else
	{
		waitpid(pid, &status, 0);
		if (((status >> 8) & 0xFF) == 130)
		{
			msh->status = 130;
			return (-1);
		}
	}
	return (0);
}

static void	heredoc_proccess(char *eof, t_msh *msh, int fd[2], bool expand)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		signal(SIGINT, hd_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line || !ft_strcmp(line, eof))
		{
			close_fds(msh);
			free(line);
			break ;
		}
		if (expand && line)
			expand_input(&line, msh->env);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	free_env(msh->env);
	free_env(msh->exp);
	clean_all(msh);
	exit(EXIT_SUCCESS);
}

static int	real_heredoc(char *eof, t_msh *msh, int fd[2], bool expand)
{
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	msh->hd_fd_write = fd[0];
	msh->hd_fd_read = fd[1];
	signal(SIGINT, reset_sig);
	if (pid == 0)
		heredoc_proccess(eof, msh, fd, expand);
	init_signal();
	close(fd[1]);
	fd[1] = -1;
	waitpid(pid, &status, 0);
	if (((status >> 8) & 0xFF) == 130)
	{
		if (msh->hd_fd_write >= 0)
		{
			close(msh->hd_fd_write);
			msh->hd_fd_write = -1;
		}
		return (msh->status = 130, -1);
	}
	return (0);
}

static int	heredoc(t_redir *list, t_msh *msh)
{
	if (!list->is_last)
	{
		if (fake_heredoc(list->filename, msh) == -1)
			return (-1);
	}
	else
	{
		if (real_heredoc(list->filename, msh, list->heredoc_fd, list->expand))
			return (-1);
	}
	return (0);
}

int	check_heredoc(t_msh	*msh)
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
					if (heredoc(list, msh) == -1)
						return (-1);
				list = list->next;
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
