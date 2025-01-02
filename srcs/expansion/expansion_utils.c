/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabefam <arabefam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:09:09 by arabefam          #+#    #+#             */
/*   Updated: 2025/01/02 10:16:46 by arabefam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	countain_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

char	check_delimiter(char *str)
{
	if (*str == '?')
		return (*(str + 1));
	if (*str == '$')
		return ('$');
	while (*str)
	{
		if ((!ft_isalnum(*str) && *str != '_'))
			return (*str);
		str++;
	}
	return (0);
}

void	join_values(char *cpy, int *i, char **token, t_e_env *env)
{
	char	delimiter;
	char	*var_name;
	char	*tmp;
	char	*value;

	if (cpy[*i] && cpy[*i] == '$' && cpy[*i + 1]
		&& (ft_isalnum(cpy[*i + 1]) || cpy[*i + 1] == '_'
			|| cpy[*i + 1] == '?'))
	{
		*i += 1;
		if (cpy[*i] != '?')
		{
			delimiter = check_delimiter(&cpy[*i]);
			var_name = ft_substr(cpy, *i, customed_strlen(&cpy[*i], delimiter));
			if (!var_name)
				return ;
			*i += customed_strlen(&cpy[*i], delimiter);
			value = ft_getenv(var_name, env);
			if (value)
				tmp = ft_strjoin(*token, value);
			else
				tmp = ft_strjoin(*token, "");
		}
		else
		{
			*i += 1;
			value = ft_itoa(42);
			tmp = ft_strjoin(*token, value);
		}
		free(*token);
		*token = ft_strdup(tmp);
		free(tmp);
		free(value);
	}
	else if (cpy[*i] && cpy[*i] == '$')
	{
		tmp = ft_strjoin(*token, "$");
		free(*token);
		*token = ft_strdup(tmp);
		free(tmp);
		*i += 1;
	}
}
