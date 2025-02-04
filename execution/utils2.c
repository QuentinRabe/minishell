/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:48:54 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/04 10:21:40 by arabefam         ###   ########.fr       */
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

void	ft_redir_in(t_cmd *ptr_cmds, int *input, bool *std)
{
	t_redir		*redir;
	t_msh		*msh;

	redir = ptr_cmds->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_IN && *input >= 0)
			close(*input);
		if (redir->type == REDIR_IN)
		{
			if (access(redir->filename, F_OK) != 0)
			{
				if (ft_error("No such file or directory: ", redir->filename, 1) == 1)
					return ;
			}
			else
			{
				*input = open(redir->filename, O_RDONLY);
				if (!redir->next && *input >= 0)
					*std = true;
				if (*input < 0)
					if (ft_error("Permission denied: ", redir->filename, 1) == 1)
						return ;
			}
		}
		redir = redir->next;
	}
	msh = get_msh(1, NULL);
	msh->status = 0;
}

void	ft_open_file(t_cmd *ptr_cmds, t_ppx *data, int *input, int *output)
{
	if (data->nb_cmd > 1)
	{
		if (data->idx > 0 && data->idx < data->nb_cmd - 1)
		{
			ft_redir_in(ptr_cmds, &data->fd[data->idx - 1][0], NULL);
			ft_redir_out(ptr_cmds, &data->fd[data->idx][1], NULL);
		}
		else if (data->idx == 0)
		{
			ft_redir_in(ptr_cmds, input, NULL);
			ft_redir_out(ptr_cmds, &data->fd[data->idx][1], NULL);
		}
		else if (data->idx == data->nb_cmd - 1)
		{
			ft_redir_in(ptr_cmds, &data->fd[data->idx - 1][0], NULL);
			ft_redir_out(ptr_cmds, output, NULL);
		}
	}
	else
	{
		ft_redir_in(ptr_cmds, input, NULL);
		ft_redir_out(ptr_cmds, output, NULL);
	}
}

int	ft_herdoc(t_cmd *ptr_cmds, char **env)
{
	t_redir	*redir;

	redir = ptr_cmds->redir_list;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->is_last)
		{
			dup2(redir->heredoc_fd[0], STDIN_FILENO);
			dup2(redir->heredoc_fd[1], STDOUT_FILENO);
			if (redir->heredoc_fd[0] >= 0)
				close(redir->heredoc_fd[0]);
			if (redir->heredoc_fd[1] >= 0)
				close(redir->heredoc_fd[1]);
			execute(ptr_cmds, env);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}
