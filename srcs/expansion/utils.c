/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:38:29 by arabefam          #+#    #+#             */
/*   Updated: 2025/02/03 20:30:57 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_varname(char *token, int i)
{
	char	*varname;
	int		varlen;
	int		j;
	char	quote;

	varlen = get_varlen(token + i);
	if (token[i] && (token[i] == '"'
			|| token[i] == '\''))
	{
		quote = token[i];
		return (ft_strdup(&quote));
	}
	varname = (char *) malloc((varlen + 1) * sizeof(char));
	if (!varname)
		return (NULL);
	j = 0;
	while (varlen > 0)
	{
		varname[j++] = token[i++];
		varlen--;
	}
	varname[j] = '\0';
	return (varname);
}

int	get_varlen(char *token)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (token[++i])
	{
		if (ft_isalnum(token[i]))
			count++;
		else if (!ft_isalnum(token[i]) && (token[i] == '?'
				|| token[i] == '$') && i == 0)
			return (1);
		else if ((!ft_isalnum(token[i]) && token[i] == '_'))
			count++;
		else if (!ft_isalnum(token[i]))
			return (count);
	}
	return (count);
}

bool	count_if_quote_case(char *token, int *count)
{
	int		i;
	char	quote;

	i = 0;
	if (token[i] == '\'' || token[i] == '"')
	{
		quote = token[i++];
		(*count)++;
		while (token[i] && token[i] != quote)
		{
			(*count)++;
			i++;
		}
		if (token[i] == quote)
		{
			(*count)++;
			return (true);
		}
	}
	return (false);
}

int	get_len_new_token(char *token, t_var *list)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && list)
		{
			len += ft_strlen(list->value);
			i += ft_strlen(list->varname);
			list = list->next;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
