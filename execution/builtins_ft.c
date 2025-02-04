/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:32:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/04 15:45:54 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_cd(char **command, int fd_in, int fd_out)
{
	char	*dir;
	t_msh	*msh;
	t_ppx	*data;
	bool	std[2];
	char	cwd[1024];

	msh = get_msh(1, NULL);
	init_stds(&std[0], &std[1]);
	data = get_data(1, NULL);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (ft_strlen_argv(msh->cmds) == 1 && std[1])
		close(fd_out);
	if (command[1] == NULL || ft_strcmp(command[1], "~") == 0)
	{
		dir = get_env(msh->env, "HOME");
		chdir(dir);
		add_new_env(msh->exp, "PWD", dir);
		add_new_env(msh->env, "PWD", dir);
		free(dir);
	}
	else if (chdir(command[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(command[1], 2);
		return (child_exit_process(data, 1), 1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		add_new_env(msh->exp, "PWD", cwd);
		add_new_env(msh->env, "PWD", cwd);
	}
	return (child_exit_process(data, 0), 0);
}

int	check_fd(int *fd_in, int *fd_out, bool *std_in, bool *std_out)
{
	t_msh	*msh;

	msh = get_msh(1, NULL);
	if (ft_strlen_argv(msh->cmds) == 1)
	{
		ft_redir_out(msh->cmds, fd_out, std_out);
		if (!*std_out)
			*fd_out = 1;
		ft_redir_in(msh->cmds, fd_in, std_in);
		if (*std_in)
			close(*fd_in);
		if (msh->status == 1)
			return (1);
	}
	return (0);
}

int	execute_pwd(t_cmd *cmds, int fd_in, int fd_out)
{
	char	cwd[1024];
	t_ppx	*data;
	bool	std[2];

	init_stds(&std[0], &std[1]);
	data = get_data(1, NULL);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (cmds->argv[1] != NULL)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		child_exit_process(data, 1);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, fd_out);
	else
	{
		close_pipe(data);
		perror("pwd");
	}
	if (ft_strlen_argv(cmds) == 1 && std[1])
		close(fd_out);
	child_exit_process(data, 0);
	return (0);
}

int	ft_exit(char **argv, int fd_in, int fd_out)
{
	t_ppx	*data;
	t_msh	*msh;
	bool	std[2];

	msh = get_msh(1, NULL);
	init_stds(&std[0], &std[1]);
	data = get_data(1, NULL);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (ft_strlen_argv(msh->cmds) == 1 && std[1])
		close(fd_out);
	ft_putendl_fd("exit", 1);
	if (argv[1] && argv[2] && exit_process(argv[1], argv[2], data, msh) == 1)
		return (1);
	else if (argv[1] && !argv[2])
	{
		if (exit_process(argv[1], NULL, data, msh) == 1)
			return (1);
	}
	else if (!argv[1])
	{
		child_exit_process(data, msh->status);
		exit(msh->status);
	}
	return (0);
}

int	execute_echo(t_cmd *cmds, int fd_in, int fd_out)
{
	char	**cmd;
	int		line;
	int		idx;
	bool	std[2];

	idx = 0;
	line = 1;
	cmd = cmds->argv + 1;
	init_stds(&std[0], &std[1]);
	if (check_fd(&fd_in, &fd_out, &std[0], &std[1]) == 1)
		return (1);
	if (ft_valid_option(cmd, &idx) == 1)
		line = 0;
	while (cmd[idx])
	{
		ft_putstr_fd(cmd[idx], fd_out);
		idx++;
	}
	if (line == 1)
		write(fd_out, "\n", 1);
	if (ft_strlen_argv(cmds) == 1 && std[1])
		close(fd_out);
	free_child();
	return (0);
}
