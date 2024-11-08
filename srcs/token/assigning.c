/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:30:14 by arabefam          #+#    #+#             */
/*   Updated: 2024/11/08 10:42:45 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	non_quote_case(char *str, int *index, int *pos, t_token *tokens)
{
	int	length;

	if (str[*index] && !is_space(str[*index]))
	{
		length = customed_strlen(&str[*index], ' ');
		tokens[*pos].value = ft_substr(str, *index, length);
		*index += length;
		*pos += 1;
	}
}

static void	quote_case(char *str, int *index, int *pos, t_token *tokens)
{
	int		length;
	char	quote;

	if ((str[*index] == '\'' || str[*index] == '"') && str[*index])
	{
		quote = str[*index];
		*index += 1;
		length = customed_strlen(&str[*index], quote);
		tokens[*pos].value = ft_substr(str, *index, length );
		*index += length;
		*pos += 1;
	}
}

void	create_tokens(t_token *tokens, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[++j])
	{
		skip_space(str, &j);
		quote_case(str, &j, &i, tokens);
		non_quote_case(str, &j, &i, tokens);
	}
}


