/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:32:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/04 09:59:16 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_cd(char **command)
{
	char	*dir;
	t_msh	*msh;
	t_ppx	*data;

	data = get_data(1, NULL);
	msh = get_msh(1, NULL);
	if (command[1] == NULL || strcmp(command[1], "~") == 0)
	{
		dir = get_env(msh->env, "HOME");
		chdir(dir);
		free(dir);
	}
	else if (chdir(command[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(command[1], 2);
		child_exit_process(data, 1);
		return (1);
	}
	child_exit_process(data, 0);
	return (0);
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

	std[0] = false;
	std[1] = false;
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

int	ft_exit(char **argv, int fd)
{
	t_ppx	*data;
	t_msh	*msh;

	data = get_data(1, NULL);
	msh = get_msh(1, NULL);
	if (ft_strlen_argv(msh->cmds) == 1)
	{
		ft_redir_out(msh->cmds, &fd, NULL);
		if (fd >= 0)
			close(fd);
		fd = 1;
	}
	ft_putendl_fd("exit", fd);
	if (argv[1] && argv[2])
	{
		if (exit_process(argv[1], argv[2], data, msh) == 1)
			return (1);
	}
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

int	execute_echo(t_cmd *cmds, int fd)
{
	char	**cmd;
	bool	std;
	int		line;
	int		idx;

	idx = 0;
	line = 1;
	std = false;
	cmd = cmds->argv + 1;
	if (ft_strlen_argv(cmds) == 1)
	{
		ft_redir_out(cmds, &fd, &std);
		if (!std)
			fd = 1;
	}
	if (ft_valid_option(cmd, &idx) == 1)
		line = 0;
	while (cmd[idx])
	{
		ft_putstr_fd(cmd[idx], fd);
		idx++;
	}
	if (line == 1)
		write(fd, "\n", 1);
	if (ft_strlen_argv(cmds) == 1 && std)
		close(fd);
	free_child();
	return (0);
}
