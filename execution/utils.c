/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:46:46 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/04 10:55:26 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strlen_argv(t_cmd *cmds)
{
	t_cmd	*ptr_cmd;
	int		i;

	i = 0;
	ptr_cmd = cmds;
	while (ptr_cmd)
	{
		if (ptr_cmd->argv[0])
			i++;
		ptr_cmd = ptr_cmd->next;
	}
	return (i);
}

void	ft_wait(t_ppx *data, int *status)
{
	int		i;
	t_msh	*msh;

	i = 0;
	close_pipe(data);
	msh = get_msh(1, NULL);
	waitpid(data->pid, status, 0);
	msh->status = (*status >> 8) & 0xFF;
	while (i < data->nb_cmd)
	{
		wait(NULL);
		i++;
	}
}

bool	is_only(char *set, char *str)
{
	int		i;
	int		j;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	if (count == ft_strlen(str))
		return (true);
	else
		return (false);
}

void	child_exit_process(t_ppx *data, int status)
{
	t_msh	*msh;

	(void) data;
	msh = get_msh(1, NULL);
	if (ft_strlen_argv(msh->cmds) != 1)
	{
		free_child();
		exit(status);
	}
	else if (ft_strlen_argv(msh->cmds) == 1)
	{
		close_heredoc_fd(msh->cmds);
		if (ft_strcmp(msh->cmds->argv[0], "exit") == 0)
		{
			if (status != -42)
			{
				free_everything(msh);
				exit(status);
			}
		}
	}
}

void	ft_redir_out(t_cmd *ptr_cmds, int *output, bool *std)
{
	t_redir		*redir;
	t_msh		*msh;

	redir = ptr_cmds->redir_list;
	while (redir)
	{
		if ((redir->type == APPEND || redir->type == TRUNC) && *output >= 0)
			close(*output);
		if (redir->type == APPEND)
			*output = open(redir->filename, O_RDWR | O_APPEND | O_CREAT, 0644);
		else if (redir->type == TRUNC)
			*output = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if ((redir->type == APPEND || redir->type == TRUNC) \
		&& *output >= 0 && std)
			*std = true;
		if ((redir->type == APPEND || redir->type == TRUNC) && *output < 0)
			if (ft_error("Permission denied: ", redir->filename, 1) == 1)
				return ;
		redir = redir->next;
	}
	msh = get_msh(1, NULL);
	msh->status = 0;
}
