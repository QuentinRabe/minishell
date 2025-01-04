/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:44:13 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 22:10:19 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	count_spaces_around(char *str, int i, int *count)
{
	if (str[i - 1] && !is_in(SPACES, str[i - 1], NULL) && str[i - 1] != str[i])
		*count += 1;
	if (str[i + 1] && str[i + 1] != str[i] && !is_in(SPACES, str[i + 1], NULL))
		*count += 1;
}

int	count_additionnal_spaces(char *str)
{
	char	quote;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			count_spaces_around(str, i, &count);
		i++;
	}
	return (count);
}

void	trim(char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	free(*str);
	*str = ft_strtrim(tmp, SPACES);
	free(tmp);
}
