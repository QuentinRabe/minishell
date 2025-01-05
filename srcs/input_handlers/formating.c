/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:44:13 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/04 23:50:03 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	adding_spaces_proccess(char *new, char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			new[j++] = quote;
			while (str[i] && str[i] != quote)
				new[j++] = str[i++];
			new[j++] = str[i++];
		}
		else if (is_in(PIPENCO, str[i], NULL))
		{
			if (str[i - 1] && !is_in(SPACES, str[i - 1], NULL) && str[i - 1] != str[i])
				new[j++] = ' ';
			new[j++] = str[i];
			if (str[i + 1] && str[i + 1] == str[i])
				new[j++] = str[i++];
			if (str[i + 1] && str[i + 1] != str[i] && !is_in(SPACES, str[i + 1], NULL))
				new[j++] = ' ';
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	printf("This is new -> %s\n", new);
}

void	add_spaces_around(char **str)
{
	char	*new;
	int		len;

	len = ft_strlen(*str) + count_additionnal_spaces(*str);
	if (len == (int) ft_strlen(*str))
		return ;
	new = (char *) malloc((len + 1) * sizeof(char));
	if (!new)
		return ;
	adding_spaces_proccess(new, *str);
}

void	trim(char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	free(*str);
	*str = ft_strtrim(tmp, SPACES);
	free(tmp);
}

void	format_input(char **str)
{
	printf("OK\n");
	trim(str);
	add_spaces_around(str);
}
