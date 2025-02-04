/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:32:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/04 10:40:17 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_builtins(void)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (ft_strlen_argv(msh->cmds) == 1)
	{
		if (ft_strcmp(msh->cmds->argv[0], "exit") == 0)
			return (1);
		else if (ft_strcmp(msh->cmds->argv[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(msh->cmds->argv[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(msh->cmds->argv[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(msh->cmds->argv[0], "export") == 0)
			return (1);
		else if (ft_strcmp(msh->cmds->argv[0], "env") == 0)
			return (1);
		else if (ft_strcmp(msh->cmds->argv[0], "unset") == 0)
			return (1);
	}
	return (0);
}

int	ft_builtins(t_msh *msh, t_cmd *ptr_cmd, char **env, int fd)
{
	if (ft_strcmp(ptr_cmd->argv[0], "exit") == 0)
		return (ft_exit(ptr_cmd->argv, -1, fd), 1);
	else if (ft_strcmp(ptr_cmd->argv[0], "cd") == 0)
		return (execute_cd(ptr_cmd->argv, -1, -1), 1);
	else if (ft_strcmp(ptr_cmd->argv[0], "pwd") == 0)
		return (execute_pwd(ptr_cmd, -1, fd), 1);
	else if (ft_strcmp(ptr_cmd->argv[0], "echo") == 0)
		return (execute_echo(ptr_cmd, -1, fd), 1);
	else if (ft_strcmp(ptr_cmd->argv[0], "export") == 0)
		return (execute_export(ptr_cmd, -1, fd), 1);
	else if (ft_strcmp(ptr_cmd->argv[0], "env") == 0)
		return (execute_env(ptr_cmd, msh->env), 1);
	else if (ft_strcmp(ptr_cmd->argv[0], "unset") == 0)
		return (execute_unset(ptr_cmd), 1);
	else if (ft_herdoc(ptr_cmd, env))
		return (1);
	return (0);
}

int	minishell(t_msh *msh, char **env)
{
	int	size;

	size = ft_strlen_argv(msh->cmds);
	if (size == 1 && ft_strcmp(msh->cmds->argv[0], "exit") == 0)
		msh->status = ft_exit(msh->cmds->argv, -1, -1);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "cd") == 0)
		msh->status = execute_cd(msh->cmds->argv, -1, -1);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "pwd") == 0)
		msh->status = execute_pwd(msh->cmds, -1, -1);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "echo") == 0)
		msh->status = execute_echo(msh->cmds, -1, -1);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "export") == 0)
		msh->status = execute_export(msh->cmds, -1, -1);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "env") == 0)
		msh->status = execute_env(msh->cmds, msh->env);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "unset") == 0)
		msh->status = execute_unset(msh->cmds);
	else
		ft_execution(msh, env);
	return (0);
}
