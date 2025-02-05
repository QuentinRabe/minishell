/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:55:37 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/05 06:46:01 by arabefam         ###   ########.fr       */
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

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	free_and_error_path(char *path, char *msg, char *cmd, int stat)
{
	free(path);
	ft_error(msg, cmd, stat);
}
