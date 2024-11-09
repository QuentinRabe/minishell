/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:14:29 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 14:56:14 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_last_dir(char **path)
{
	int		i;
	char	**splitted;
	char	*tmp;

	splitted = ft_split(*path, '/');
	i = -1;
	while (splitted[++i] != NULL)
		;
	i -= 1;
	free(*path);
	*path = ft_strdup(splitted[i]);
	i = -1;
	while (splitted[++i])
	{
		free(splitted[i]);
	}
	free(splitted);
	tmp = ft_strjoin(*path, " -> ");
	free(*path);
	*path = ft_strdup(tmp);
	free(tmp);
}

char	*get_prompt_cwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	get_last_dir(&path);
	return (path);
}
