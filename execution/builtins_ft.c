/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:32:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/03 09:30:00 by arabefam         ###   ########.fr       */
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

int	execute_pwd(t_cmd *cmds, int fd)
{
	char	cwd[1024];
	t_ppx	*data;

	data = get_data(1, NULL);
	if (fd < 0)
	{
		fd = 1;
		ft_redir_out(cmds, &fd);
	}
	if (cmds->argv[1] != NULL)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		child_exit_process(data, 1);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, fd);
	else
	{
		close_pipe(data);
		perror("pwd");
	}
	child_exit_process(data, 0);
	return (0);
}

int	ft_exit(char **argv, int fd)
{
	t_ppx	*data;

	data = get_data(1, NULL);
	if (fd < 0)
		fd = 1;
	ft_putendl_fd("exit", fd);
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("msh: exit : too many argument", 2);
		child_exit_process(data, -42);
		return (1);
	}
	else
	{
		if (argv[1] && !is_only(DIGITS, argv[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(" : numeric argument required", 2);
			child_exit_process(data, 2);
		}
		else if (argv[1] && is_only(DIGITS, argv[1]))
			child_exit_process(data, ft_atoi(argv[1]) % 256);
		child_exit_process(data, 0);
		exit(0);
	}
	return (0);
}

int	execute_echo(t_cmd *cmds, int fd)
{
	char	**cmd;
	int		line;
	int		idx;

	idx = 0;
	line = 1;
	cmd = cmds->argv + 1;
	if (fd < 0)
	{
		fd = 1;
		ft_redir_out(cmds, &fd);
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
	free_child();
	return (0);
}
