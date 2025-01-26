/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rravelom <rravelom@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:11:16 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/18 10:11:17 by rravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_check(char *command)
{
	int	i;

	i = 0;
	if (command[i] != '-')
		return (0);
	else
		i++;
	while (command[i])
	{
		if (command[i] != 'n')
			return (0);
		else
			i++;
	}
	return (1);
}

int	ft_valid_option(char **command, int *idx)
{
	while (command[*idx])
	{
		if (!ft_check(command[*idx]))
		{
			if (*idx == 0)
				return (0);
			else
				return (1);
		}
		else
			*idx += 1;
	}
	if (*idx == 0)
		return (0);
	return (1);
}

void	ft_redir_fd(t_cmd *ptr_cmds, int *input, int *output)
{
	t_redir		*redir;

	redir = ptr_cmds->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			*input = open(redir->filename, O_RDONLY);
		else if (redir->type == APPEND)
			*output = open(redir->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
		else if (redir->type == TRUNC)
			*output = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		redir = redir->next;
		if (redir)
		{
			if (redir->type == REDIR_IN)
				close(*input);
			if (redir->type == APPEND || redir->type == TRUNC)
				close(*output);
		}
	}
}

void	ft_open_file(t_cmd *ptr_cmds, t_ppx *pipex, int *input, int *output)
{
	if (pipex->nb_cmd > 1)
	{
		if (pipex->idx > 0 && pipex->idx < pipex->nb_cmd - 1)
			ft_redir_fd(ptr_cmds, &pipex->fd[pipex->idx - 1][0], \
			&pipex->fd[pipex->idx][1]);
		else if (pipex->idx == 0)
			ft_redir_fd(ptr_cmds, input, &pipex->fd[pipex->idx][1]);
		else if (pipex->idx == pipex->nb_cmd - 1)
			ft_redir_fd(ptr_cmds, &pipex->fd[pipex->idx - 1][0], output);
	}
	else
		ft_redir_fd(ptr_cmds, input, output);
}

int	ft_herdoc(t_cmd *ptr_cmds, char **env)
{
	t_redir	*redir;

	redir = ptr_cmds->redir_list;
	while (redir->type == HEREDOC)
	{
		if (redir->is_last)
		{
			dup2(redir->heredoc_fd[0], STDIN_FILENO);
			dup2(redir->heredoc_fd[1], STDOUT_FILENO);
			close(redir->heredoc_fd[0]);
			close(redir->heredoc_fd[1]);
			execute(ptr_cmds, env, STDIN_FILENO, STDOUT_FILENO);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}
