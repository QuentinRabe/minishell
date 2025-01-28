/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:36:13 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/28 08:05:35 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_new_value(char *new, char **splitted)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	while (splitted[++i])
	{
		j = -1;
		while (splitted[i][++j])
			new[k++] = splitted[i][j];
		new[k++] = ' ';
	}
	new[--k] = '\0';
	free_argv(splitted);
}

void	check_filename_in_dq(char *token, t_token *curr)
{
	if (token[0] == '"'
		&& token[ft_strlen(token) - 1] == '"')
		curr->in_dq = true;
	else
		curr->in_dq = false;
}

void	one_espace_value(char *value, t_var *new)
{
	char	*new_value;
	char	**splitted;
	int		spaces;
	size_t	len;

	spaces = 0;
	splitted = ft_split_set(value, SPACES);
	len = get_splitted_lenght(splitted, &spaces);
	new_value = (char *) malloc((len + spaces + 1) * sizeof(char));
	if (!new_value)
		return ;
	create_new_value(new_value, splitted);
	free(value);
	new->value = ft_strdup(new_value);
	free(new_value);
}

size_t	get_splitted_lenght(char **splitted, int *spaces)
{
	int		i;
	int		j;
	size_t	len;

	len = 0;
	i = -1;
	while (splitted[++i])
	{
		j = -1;
		while (splitted[i][++j])
			len++;
		(*spaces)++;
	}
	(*spaces)--;
	return (len);
}
