/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:59:19 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/19 09:00:02 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_varlen_hd(char *token)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	if (!count_if_quote_case(token, &count))
	{
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
	}
	return (count);
}

char	*get_varname_hd(char *token, int i)
{
	char	*varname;
	int		varlen;
	int		j;

	varlen = get_varlen_hd(token + i);
	if (varlen == 0)
		return (ft_strdup("$"));
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

int	get_len_new_input_hd(char *input, t_var *list)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && list)
		{
			len += ft_strlen(list->value);
			i += ft_strlen(list->varname) + 1;
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
