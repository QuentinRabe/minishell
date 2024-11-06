/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:50:17 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/06 11:14:01 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_last_a_slash(char *path)
{
	return (path[ft_strlen(path) - 1] == '/');
}

static void	add_last_slash(char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!is_last_a_slash(env[i]))
		{
			tmp = ft_strjoin(env[i], "/");
			free(env[i]);
			env[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
}

static void	remove_path_label(char **path)
{
	char	*tmp;

	tmp = ft_strdup(*path + 5);
	free(*path);
	*path = ft_strdup(tmp);
	free(tmp);
}

char	**extract_path_from_env(char **env)
{
	int		i;
	char	**result;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			result = ft_split(env[i], ':');
			remove_path_label(&result[0]);
			add_last_slash(result);
			return (result);
		}
	}
	return (NULL);
}
