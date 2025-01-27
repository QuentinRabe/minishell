/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:32:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/27 10:55:50 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_builtins(t_msh *msh, t_cmd *ptr_cmd, char **env)
{
	if (ft_strcmp(ptr_cmd->argv[0], "exit") == 0)
		ft_exit(ptr_cmd->argv);
	else if (ft_strcmp(ptr_cmd->argv[0], "cd") == 0)
		execute_cd(ptr_cmd->argv);
	else if (ft_strcmp(ptr_cmd->argv[0], "pwd") == 0)
		execute_pwd(ptr_cmd);
	else if (ft_strcmp(ptr_cmd->argv[0], "echo") == 0)
		execute_echo(ptr_cmd);
	else if (ft_strcmp(ptr_cmd->argv[0], "export") == 0)
		execute_export(msh);
	else if (ft_herdoc(ptr_cmd, env))
		return (1);
	if (ft_strcmp(ptr_cmd->argv[0], "exit") == 0 \
	|| ft_strcmp(ptr_cmd->argv[0], "cd") == 0 \
	|| ft_strcmp(ptr_cmd->argv[0], "pwd") == 0 \
	|| ft_strcmp(ptr_cmd->argv[0], "echo") == 0 \
	|| ft_strcmp(ptr_cmd->argv[0], "export") == 0)
		return (1);
	return (0);
}

int	minishell(t_msh *msh, char **env)
{
	int	size;

	size = ft_strlen_argv(msh->cmds);
	if (size == 1 && ft_strcmp(msh->cmds->argv[0], "exit") == 0)
		ft_exit(msh->cmds->argv);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "cd") == 0)
		execute_cd(msh->cmds->argv);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "pwd") == 0)
		execute_pwd(msh->cmds);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "echo") == 0)
		execute_echo(msh->cmds);
	else if (size == 1 && ft_strcmp(msh->cmds->argv[0], "export") == 0)
		execute_export(msh);
	else
		ft_execution(msh, env);
	return (0);
}
