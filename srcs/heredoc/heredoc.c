/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:22:21 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/28 13:27:09 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fake_heredoc(char *eof, t_msh *msh)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	signal(SIGINT, reset_sig);
	if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, hd_signal_handle_fake);
			line = readline("here_doc: ");
			if (!line || !ft_strcmp(line, eof))
			{
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
	else
		wait(NULL);
}

static void	heredoc_proccess(char *eof, t_msh *msh, int fd[2], bool expand)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		signal(SIGINT, hd_signal_handle);
		line = readline("here_doc: ");
		if (!line || !ft_strcmp(line, eof))
		{
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

static void	real_heredoc(char *eof, t_msh *msh, int fd[2], bool expand)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	signal(SIGINT, reset_sig);
	if (pid == 0)
		heredoc_proccess(eof, msh, fd, expand);
	close(fd[1]);
	wait(NULL);
}

static void	heredoc(t_redir *list, t_msh *msh)
{
	if (!list->is_last)
		fake_heredoc(list->filename, msh);
	else
		real_heredoc(list->filename, msh, list->heredoc_fd, list->expand);
	init_signal();
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
		cmd = cmd->next;
	}
}
