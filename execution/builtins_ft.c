/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rravelom <rravelom@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:32:39 by rravelom          #+#    #+#             */
/*   Updated: 2025/01/18 08:23:23 by rravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header.h"

void	execute_cd(char **command)
{
	if (command[1] == NULL || strcmp(command[1], "~") == 0)
		chdir(getenv("HOME"));
	else if (chdir(command[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(command[1], 2);
		write(1, "\n", 1);
	}
}

void	clear(char **command)
{
	if (command[1] != NULL)
		ft_putendl_fd("clear: too many arguments", 2);
	write(1, "\033[2J\033[H", 8);
}

void	execute_pwd(t_cmd *cmds)
{
	char	cwd[1024];
	int		fd;

	fd = 1;
	ft_redir_fd(cmds, 0, &fd);
	if (cmds->argv[1] != NULL)
		ft_putendl_fd("clear: too many arguments", 2);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, fd);
	else
		perror("pwd");
}

void	ft_exit(char **argv)
{
	ft_putendl_fd("exit", 1);
	if (argv[1] != NULL)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(" : numeric argument required", 2);
	}
	exit(0);
}

void	execute_echo(t_cmd *cmds)
{
	int		fd;
	char	**cmd;
	int		line;
	int		idx;

	idx = 0;
	line = 1;
	cmd = cmds->argv + 1;
	fd = 1;
	ft_redir_fd(cmds, 0, &fd);
	if (ft_valid_option(cmd, &idx) == 1)
		line = 0;
	while (cmd[idx])
	{
		ft_putstr_fd(cmd[idx], fd);
		idx++;
	}
	if (line == 1)
		write(fd, "\n", 1);
}
