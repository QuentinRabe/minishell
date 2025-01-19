/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:44:13 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/19 09:04:52 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipenco_case(char *str, char *new, int *i, int *j)
{
	if ((*i - 1) > 0 && (str[*i - 1] && !is_in(SPACES, str[*i - 1], NULL)
			&& str[*i - 1] != str[*i]))
	{
		new[*j] = ' ';
		*j += 1;
	}
	new[*j] = str[*i];
	*j += 1;
	if (str[*i + 1] && str[*i + 1] != str[*i]
		&& !is_in(SPACES, str[*i + 1], NULL))
	{
		new[*j] = ' ';
		*j += 1;
	}
	*i += 1;
}

static void	adding_spaces_proccess(char *new, char *str)
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
			pipenco_case(str, new, &i, &j);
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
}

static void	add_spaces_around(char **str)
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
	free(*str);
	*str = new;
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
	add_history(*str);
	trim(str);
	add_spaces_around(str);
}
