/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:07:17 by rravelom          #+#    #+#             */
/*   Updated: 2025/02/02 09:41:59 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_cmd(char *path)
{
	char	**splitted;
	int		i;
	char	*result;

	splitted = ft_split(path, '/');
	i = -1;
	while (splitted[++i])
		;
	result = ft_strdup(splitted[i - 1]);
	free_argv(splitted);
	return (result);
}

int is_directory(const char *path) {
	struct stat path_stat;

	if (stat(path, &path_stat) != 0) {
		perror("stat");
		return 0;
	}
	return S_ISDIR(path_stat.st_mode);
}

int	check_absolute_path(char *path, char **cmd)
{
	if (is_in(path, '/', NULL))
	{
		if (access(path, F_OK) == 0)
		{
			if (is_directory(path))
				return (-2);
			*cmd = get_cmd(path);
			return (0);
		}
		else
			return (-1);
	}
	return (1);
}


char	*find_path(char *cmd, char **arge)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = 0;
	if (!cmd || !cmd[0])
		return (NULL);
	while (arge[i] && ft_strnstr(arge[i], "PATH", 4) == 0)
		i++;
	if (!arge[i])
		return (NULL);
	paths = ft_split(arge[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_argv(paths);
	return (NULL);
}

int	execute(t_cmd *ptr_cmds, char **arge)
{
	char	*path;
	char	*cmd;
	int		res;

	cmd = NULL;
	res = check_absolute_path(ptr_cmds->argv[0], &cmd);
	if (res == 0)
	{
		path = ft_strdup(ptr_cmds->argv[0]);
		free(ptr_cmds->argv[0]);
		ptr_cmds->argv[0] = ft_strdup(cmd);
		free(cmd);
	}
	else if (res == -1)
		ft_error("no such file or directory: ", ptr_cmds->argv[0], 127);
	else if (res == -2)
		ft_error("is a directory: ", ptr_cmds->argv[0], 126);
	else
		path = find_path(ptr_cmds->argv[0], arge);
	if (!path)
		ft_error("command not found: ", ptr_cmds->argv[0], 127);
	else if (access(path, X_OK) != 0)
	{
		free(path);
		ft_error("permission denied: ", ptr_cmds->argv[0], 126);
	}
	execve(path, ptr_cmds->argv, arge);
	free_everything(get_msh(1, NULL));
	exit (127);
}
