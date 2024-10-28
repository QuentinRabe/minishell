/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:14:29 by arabefam          #+#    #+#             */
/*   Updated: 2024/10/21 09:58:29 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_color(char *color, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(color, *path);
	free(*path);
	*path = tmp;
	tmp = ft_strjoin(*path, RS);
	free(*path);
	*path = tmp;
	tmp = ft_strjoin(*path, "\n");
	free(*path);
	*path = tmp;
}

static void	get_last_dir(char **path)
{
	int		i;
	char	**splitted;

	splitted = ft_split(*path, '/');
	i = -1;
	while (splitted[++i] != NULL)
		;
	i -= 1;
	free(*path);
	*path = ft_strdup(splitted[i]);
	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
}

char	*get_prompt_cwd(char *color)
{
	char	*path;

	path = getcwd(NULL, 0);
	get_last_dir(&path);
	add_color(color, &path);
	return (path);
}
