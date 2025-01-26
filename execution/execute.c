/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rravelom <rravelom@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:07:17 by rravelom          #+#    #+#             */
/*   Updated: 2024/08/04 10:07:22 by rravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*find_path(char *cmd, char **arge)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = 0;
	while (ft_strnstr(arge[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(arge[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

int	execute(t_cmd *ptr_cmds, char **arge, int input_fd, int output_fd)
{
	char	*path;

	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	path = find_path(ptr_cmds->argv[0], arge);
	if (!path)
		ft_error("command not found: ", ptr_cmds->argv[0], 127);
	if (execve(path, ptr_cmds->argv, arge) == -1)
		ft_error("command execution error: ", ptr_cmds->argv[0], 127);
	return (0);
}
